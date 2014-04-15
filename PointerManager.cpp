//----------------------------------------------------------------------
// VMouse - OpenCV Virtual Mouse (HCI)
// Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------
#include "PointerManager.h"
#include "SystemConfiguration.h"

PointerManager::PointerManager() : QObject()
{
    kalmanFilter = KalmanFilter(4,2);
    framesWithoutPoints = 0;
    isPointerActive = false;

    kalmanFilter.statePre.at<float>(0) = 0;
    kalmanFilter.statePre.at<float>(1) = 0;
    kalmanFilter.statePre.at<float>(2) = 0;
    kalmanFilter.statePre.at<float>(3) = 0;
    kalmanFilter.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,0,0,   0,1,0,0,  0,0,1,0,  0,0,0,1);

    setIdentity(kalmanFilter.measurementMatrix);
    setIdentity(kalmanFilter.processNoiseCov,Scalar::all(1e-4));
    setIdentity(kalmanFilter.measurementNoiseCov,Scalar::all(SystemConfiguration::kf_noise));
    setIdentity(kalmanFilter.errorCovPost, Scalar::all(0.2));
    measurement = Mat_<float>(2,1);
    measurement.setTo(Scalar(0));
}

void PointerManager::updateFrameData(vector<Point> pointsData)
{
    // get the number of points in active frame
    int currentPointsSize = pointsData.size();
    // check if there is any point data available
    if(currentPointsSize > 0)
    {
        // set frame without points to zero because we got a point in this frame
        framesWithoutPoints = 0;
        // check if there was a active point previously
        if(isPointerActive)
        {
            // update the previous point to current point of previous frame
            previousPointer = currentPointer;
            // get the new top point
            Point newPointer = getTopMostPoint(pointsData);
            // check if there is only one point
            if(currentPointsSize == 1)
            {
                // set current point of this frame to new top point
                // as there is only one point in this frame
                currentPointer = newPointer;
            }
            // there are more than one point is there in current frame
            else
            {
                // check if the current top point is in magnet region
                // of previous frames current point
                if(isInMagnetArea(currentPointer,newPointer))
                {
                    // update current point of this frame to
                    // new top point
                    currentPointer = newPointer;
                }
                // current top point is not in magnet region of previous point
                else
                {
                    // check if there is any other suitable point in the
                    // magent regioon of the previous frames current point
                    Point suitablePoint;
                    bool isSuitablePointFound = false;
                    for(int i = 0; i< pointsData.size(); i++)
                    {
                        if(isInMagnetArea(currentPointer, pointsData[i]))
                        {
                            suitablePoint = pointsData[i];
                            isSuitablePointFound = true;
                            break;
                        }
                    }
                    // if any suitable point found
                    if(isSuitablePointFound)
                    {
                        // set current point to suitable point
                        currentPointer = suitablePoint;
                    }
                    else
                    {
                        // set current point to new point
                        currentPointer = newPointer;
                    }
                }
            }

        }
        // there is no active point in previous frame
        else
        {
            // set top most point as active point
            currentPointer = getTopMostPoint(pointsData);
            // mark that there will be active pointer
            isPointerActive = true;
        }

        // set current point to average of current point and previous point to reduce noise
        currentPointer = Point( (double)(currentPointer.x+previousPointer.x)/2.0, (double)(currentPointer.y + previousPointer.y)/2.0);
    }
    // frame without any points
    else
    {
        // check if the last N frames are without any points
        if(framesWithoutPoints < SystemConfiguration::fwp_thresh)
        {
            // increase the count to track how many frames it was without points
            framesWithoutPoints ++;
        }
        // there is no points for last N frames
        else
        {
            // mark that there is no active pointer
            isPointerActive = false;
        }
    }
}

Point PointerManager::getTopMostPoint(vector<Point> pointsData)
{
    int topY = 9999;
    int topId = 0;
    for(int i = 0; i< pointsData.size(); i++)
    {
        if(pointsData[i].y < topY)
        {
            topY = pointsData[i].y;
            topId = i;
        }
    }
    return pointsData[topId];
}

bool PointerManager::isInMagnetArea(Point previousPoint, Point currentPoint)
{
    Rect magnetRegion;
    magnetRegion.x = previousPoint.x - SystemConfiguration::fm_radius;
    magnetRegion.y = previousPoint.y - SystemConfiguration::fm_radius;
    magnetRegion.width = 2 * SystemConfiguration::fm_radius;
    magnetRegion.height = 2 * SystemConfiguration::fm_radius;
    return magnetRegion.contains(currentPoint);
}

bool PointerManager::isPointerAvailable()
{
    return isPointerActive;
}

Point PointerManager::getActivePointer()
{
    return currentPointer;
}

Point PointerManager::getFilteredPointer()
{
    setIdentity(kalmanFilter.measurementNoiseCov,Scalar::all(SystemConfiguration::kf_noise));
    kalmanFilter.predict();
    measurement(0)= currentPointer.x;
    measurement(1) = currentPointer.y;
    Mat estimated = kalmanFilter.correct(measurement);
    Point statePt(estimated.at<float>(0),estimated.at<float>(1));
    return statePt;
}
