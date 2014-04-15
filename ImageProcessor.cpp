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
#include "ImageProcessor.h"
#include <opencv2/opencv.hpp>
#include "MatToQImageConverter.h"
#include <QImage>
#include <string>
#include "SystemConfiguration.h"

using namespace cv;

ImageProcessor::ImageProcessor()
{
    //------------------------------------------------------
    // set variables to defaults
    //------------------------------------------------------
    // set mouse down event to false
    isMouseDown = false;
    // set mouse click event to false
    isClickActivated = false;
    // set mouse double click event to false
    isDoubleClickActivated = false;
    // set mouse down deactivation counter to zero
    framesWithMouseDownDeactivationOunter = 0;
    // set mouse down activation counter to zero
    framesWithMouseDownActivationCounter = 0;
    // set mouse click activation counter to zero
    framesWithClickActivationCounter = 0;
    // set mouse click deactivation counter to zero
    framesWithDoubleClickDeactivationCounter = 0;
    // set mouse double click activation counter to zero
    framesWithDoubleClickActivationCounter = 0;
    // set mouse double click deactivation counter to zero
    framesWithClickDeactivationCounter = 0;
    // set mouse event reset counter to zero
    framesWithResetCounter = 0;
}


vector<Mat> ImageProcessor::getprocessedImage(Mat image)
{
    //------------------------------------------------------
    // init variables
    //------------------------------------------------------
    // contains the processed image and the drawing image that need to be shown in display
    vector<Mat> outputs;
    // contains the area of a contour
    double contour_area;
    // contains set of all contours in current frame
    vector< vector<Point> > contours;
    // contains hierarchy of the detected contours
    vector<Vec4i> hierarchy;
    // detnotes largest contour in current frame
    int largestContour = -1;
    // denotes area of the largest contour in current frame
    double largestArea = 0;
    // denotes the image after opening is performed
    Mat openingImage;
    // denotes the image after bluring is performed
    Mat bluredImage;
    // denotes the image after threshold is performed
    Mat threshImage;
    // denotes the image after closing is performed
    Mat closingImage;
    // denotes temporary image which is used for contour detection
    Mat temp_image;

    // clear the set of final points detected in the previous frame
    finalPoints.clear();

    //------------------------------------------------------
    // define kernels
    //------------------------------------------------------
    // create the kernel for opening operation based on the current configuration
    Mat kernelOpen = getStructuringElement(MORPH_ELLIPSE,Size(SystemConfiguration::opening_kernel_size,SystemConfiguration::opening_kernel_size));
    // create the kernel for closing operation based on the current configuration
    Mat kernelClose = getStructuringElement(MORPH_ELLIPSE,Size(SystemConfiguration::closing_kernel_size,SystemConfiguration::closing_kernel_size));


    //------------------------------------------------------
    // apply preprocessing on the input image
    //------------------------------------------------------
    // apply gaussian blur to the input image
    GaussianBlur(image, bluredImage, Size(SystemConfiguration::blur_kernel_size,SystemConfiguration::blur_kernel_size), SystemConfiguration::blur_sigma);
    // apply threshold on the blured image to create binary image
    threshold(bluredImage,threshImage,SystemConfiguration::image_threshold,255,THRESH_BINARY);
    // apply closing on the binary image to onnect small fragments
    morphologyEx(threshImage,closingImage,MORPH_CLOSE,kernelClose);
    // apply opening on the closing image to disconnect large fragments
    morphologyEx(closingImage,openingImage,MORPH_OPEN,kernelOpen);


    //------------------------------------------------------
    // find largest blob in the image based on the area threshold
    //------------------------------------------------------
    // create a clone of the preprocessed image
    openingImage.copyTo(temp_image);
    // find all contours in the preprocessed image
    findContours(temp_image, contours, hierarchy, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    // if there any contours exist in the image then detect the largest blob
    if ( !contours.empty()) {
        // for each contour in the image, iterate list of contours
        for (size_t i=0; i<contours.size(); ++i) {
            // calculate area of the contour
            contour_area = contourArea(contours[i]);
            // check if the area of the contour is greater than the predefined area threshold
            if ( contour_area > SystemConfiguration::area_thresh)
                // check if the current contour is greater than the previous detected largest contour
                if(largestArea < contour_area)
                {
                    // set largest contour to this contour
                    largestContour = i;
                    // set largest contour area to this contour
                    largestArea = contour_area;
                }
        }
    }

    //------------------------------------------------------
    // apply convex detection, convex defects detection and defects elimination to detect the points
    //------------------------------------------------------
    // create a blank image for drawing which will be shown in the GUI
    Mat drawingCanvas(openingImage.rows,openingImage.cols, CV_8UC3);
    // set the blank image to white
    drawingCanvas.setTo(Scalar(255,255,255));

    // check if there exist any detected largest contour
    if(largestContour != -1) {
        // apply Ramer–Douglas–Peucker algorithm to smooth counour points
        approxPolyDP(Mat(contours[largestContour]),contours[largestContour],SystemConfiguration::dp_epsilon,true);

        // draw the largest smooth contour points for display purpose
        drawContours( drawingCanvas, contours, largestContour, Scalar(100,100,100), -1);

        // calculate the bounding rectangle of the largest contour
        boundingRectect = boundingRect(Mat(contours[largestContour]));
        // draw the bounding rectangle for display purpose
        rectangle(drawingCanvas,boundingRectect,Scalar(255,255,0),2);

        // contains the convex hull for display purpose
        vector<vector<Point> > hull(1);
        // calculate the cinvex hull for display purpose
        convexHull( Mat(contours[largestContour]), hull[0], false );
        // draw the convex hull for display purpose
        drawContours( drawingCanvas, hull, 0, Scalar(0,0,0), 2);

        // contains convex hull for calculation purpose
        vector<int> chull;

        // detect the convex hull of the largest contour for calculation purpose
        convexHull( Mat(contours[largestContour]), chull, false );

        // check if the largest contour has atleast 3 points to detect defects
        if(contours[largestContour].size() > 3 )
            // check if the convex hull has atleast 2 points to detect defects
            if(chull.size() > 2 )
            {
                // vector that contains the defects in the convex hull
                vector<Vec4i> defects;
                // calculate convexity defects for the largest contour
                convexityDefects(contours[largestContour],chull,defects);
                // eliminate the difects by their dimention constrant
                vector<Vec4i> defects_stage1 = eleminateDefectsByDimentation(defects,contours[largestContour]);
                // eliminate the difects by region constrant
                vector<Vec4i> defects_stage2 = eleminateDefectsByregion(defects_stage1,contours[largestContour],boundingRectect);

                // calculate the final points by eliminating the points that are too close to each other
                finalPoints = removeRedundantEndPoints(defects_stage2,contours[largestContour]);

                // calculate moment of the largest contour to get center of gravity
                Moments momentum = moments(contours[largestContour],true);
                // calculate center of gravity of the largest contour from moment data
                Point centerofGravity = Point(momentum.m10/momentum.m00 , momentum.m01/momentum.m00);
                // draw center of gravity
                circle(drawingCanvas,centerofGravity,10,Scalar(0,0,255),-1);

                // iterate through each points in the list of final points
                for(int i=0; i< finalPoints.size(); i++)
                {
                    // draw circle at the point for display purpose
                    circle(drawingCanvas,finalPoints[i],10,Scalar(255,0,0),-1);
                    // draw a line from the center of gravity for display purpose
                    line(drawingCanvas,centerofGravity,finalPoints[i],Scalar(0,0,255),2);
                }

                // check if final points size is zero then find the top most point
                if(finalPoints.size() == 0)
                {
                    // find the point to represent top point
                    Point pt = findTopPoint(contours[largestContour], centerofGravity);
                    // check if the top point is a valid point
                    if(pt.x != 9999 && pt.y != 9999){
                        // add the top point to the list of final points
                        finalPoints.push_back(pt);
                        // draw a circle at the top point for display purpose
                        circle(drawingCanvas,pt,10,Scalar(0,100,0),-1);
                        // draw a line from center of gravity for display purpose
                        line(drawingCanvas,centerofGravity,pt,Scalar(100,255,50),2);
                    }
                }
            }
    }
    // add opening image to set of output images
    outputs.push_back(openingImage);
    // add drawing image to set of output images
    outputs.push_back(drawingCanvas);
    // return set of output images
    return outputs;
}

Mat ImageProcessor::getOutputImage()
{
    //------------------------------------------------------
    // draw the output image to show raw data points
    //------------------------------------------------------
    // indicates the id of the point
    int point_count = 1;
    // image for drawing purpose
    Mat drawingCanvas = Mat::zeros(SystemConfiguration::image_size,SystemConfiguration::image_size,CV_8UC3);
    // set the drawing image to white
    drawingCanvas.setTo(Scalar(255,255,255));

    // denotes the rectangle for which mouse pointer is valid
    Rect roi;
    // set the x position of region of interest
    roi.x = SystemConfiguration::topX;
    // set the y position of region of interest
    roi.y = SystemConfiguration::topY;
    // set the width of region of interest
    roi.width = SystemConfiguration::bottomX - SystemConfiguration::topX;
    // set the height of region of interest
    roi.height = SystemConfiguration::bottomY - SystemConfiguration::topY;
    // draw the valid mouse region for display purpose
    rectangle(drawingCanvas,roi,Scalar(150,150,150),-1);

    // iterate through each points in the set of all final points
    for(int i=0;i<finalPoints.size();i++)
    {
        // draw a circle at the point for display purpose
        circle(drawingCanvas,finalPoints[i],10,Scalar(0,10,200),-1);
        // create a string stream to convert number to string
        stringstream sStream;
        // convert the point id to string
        sStream<<point_count;
        // draw the point id for display purpose
        putText(drawingCanvas,sStream.str(),finalPoints[i],FONT_HERSHEY_PLAIN,4,Scalar(0,0,0),3);
        //incriment the point id
        point_count++;
    }

    //------------------------------------------------------
    // perform estimation and show estimated data
    //------------------------------------------------------
    // update the current frames data to the pointer manager for estimation purpose
    pointerManager.updateFrameData(finalPoints);

    // check if there is any estimate pointer available
    if(pointerManager.isPointerAvailable())
    {
        // get the active pointer location from point manager
        Point activePoint = pointerManager.getActivePointer();
        // draw a cross at the active pointer
        line(drawingCanvas,Point(activePoint.x - 20,activePoint.y),Point(activePoint.x + 20,activePoint.y),Scalar(255,0,0),4);
        line(drawingCanvas,Point(activePoint.x,activePoint.y - 20),Point(activePoint.x,activePoint.y + 20),Scalar(255,0,0),4);

        // get the estimated mouse pointer location
        Point activeFilteredPoint = pointerManager.getFilteredPointer();
        // draw a circle at the estimated point
        circle(drawingCanvas,activeFilteredPoint,20,Scalar(0,255,0),3);
    }
    // return the drawing canvas
    return drawingCanvas;
}

vector<Vec4i> ImageProcessor::eleminateDefectsByDimentation(vector<Vec4i> defects,vector<Point> contours){
    //------------------------------------------------------
    // eliminate defects by its dimention constrant
    //------------------------------------------------------
    // contains the filtered defects
    vector<Vec4i> filteredDefects;
    // iterate through each defect points
    for(int i = 0; i< defects.size(); i++)
    {
        // get the starting point of the defect
        Point ptStart(contours[defects[i][0]]);
        // get the ending point of the defect
        Point ptEnd(contours[defects[i][1]]);
        // get the depth point of the defect
        Point ptFar(contours[defects[i][2]]);
        // calculate distance from starting point to depth point
        float distance1 = distanceP2P(ptStart, ptFar);
        // calculate destance from ending point to depth point
        float distance2 = distanceP2P(ptEnd, ptFar);
        // calculate the angle between line(start,far) and line(end,far)
        float angle = getAngle(ptStart, ptFar, ptEnd);
        // check if the distance and angle are within the predefined constrant
        if((distance1 >= SystemConfiguration::dt_min) &&
                (distance1 <= SystemConfiguration::dt_max) &&
                (distance2 >= SystemConfiguration::dt_min) &&
                (distance2 <= SystemConfiguration::dt_max) &&
                (angle >= SystemConfiguration::at_min) &&
                (angle <= SystemConfiguration::at_max) ){
            // add the defect to the list of filtered defects
            filteredDefects.push_back(defects[i]);
        }
    }
    // return the set of filtered defects
    return filteredDefects;
}

vector<Vec4i> ImageProcessor::eleminateDefectsByregion(vector<Vec4i> defects, vector<Point>contours, Rect boundingRect)
{
    //------------------------------------------------------
    // eliminate defects by its region constrant
    //------------------------------------------------------
    // denotes the region of interest
    Rect regionFilter;
    // set regions x location to bounding rectangles x location
    regionFilter.x = boundingRect.x;
    // set regions y location to bounding rectangles y location
    regionFilter.y = boundingRect.y;
    // set with of the region to bounding rectangles width
    regionFilter.width = boundingRect.width;
    // set height of the region to bounding rectangles widh % threshold
    regionFilter.height = boundingRect.height * SystemConfiguration::rh_thresh;
    // denotes the set of filtered defects
    vector<Vec4i> newDefects;
    // iterate throush all defects
    for(int i = 0; i< defects.size(); i++)
    {
        // get the start of the defect
        Point ptStart(contours[defects[i][0]]);
        // get the end of the defect
        Point ptEnd(contours[defects[i][1]]);
        // get the depth of the defect
        Point ptFar(contours[defects[i][2]]);
        // check if all the points belong to region of interest
        if(regionFilter.contains(ptStart) && regionFilter.contains(ptEnd) && regionFilter.contains(ptFar)){
            // add the defect to the list of filtered defects
            newDefects.push_back(defects[i]);
        }
    }
    // return list of filtered defects
    return newDefects;
}

Point ImageProcessor::findTopPoint(vector<Point> contours, Point centerOfGravity)
{
    //------------------------------------------------------
    // find the top most point in a contour such that top point is above center of gravity
    //------------------------------------------------------
    // set the point to a invalid location
    Point point(9999,9999);
    // iterate through all the points in the conture
    for(int i = 0; i< contours.size(); i++)
    {
        // check if the y coordinate is less than the previous saved point {0 == top most | y axis is from top to bottom direction}
        if(contours[i].y <= point.y &&
                contours[i].y < centerOfGravity.y &&
                distanceP2P(centerOfGravity,contours[i])> 0)
        {
            // update the point to new top point
            point = contours[i];
        }
    }
    // return the top most point
    return point;
}

float ImageProcessor::distanceP2P(Point a, Point b){
    // calculate the distance between points
    float distance = sqrt(fabs( pow(a.x-b.x,2) + pow(a.y-b.y,2) )) ;
    // return the distance
    return distance;
}

float ImageProcessor::getAngle(Point s, Point f, Point e){
    // get angle between three points representing two lines
    float l1 = distanceP2P(f,s);
    float l2 = distanceP2P(f,e);
    float dot=(s.x-f.x)*(e.x-f.x) + (s.y-f.y)*(e.y-f.y);
    float angle = acos(dot/(l1*l2));
    angle=angle*180/PI;
    // return the angle
    return angle;
}

vector<Point> ImageProcessor::removeRedundantEndPoints(vector<Vec4i> newDefects,vector<Point> contours){
    //------------------------------------------------------
    // remove points that are too close and keep only one of them
    //------------------------------------------------------
    // set of filtered points
    vector<Point> pointsFinal;
    // set of all points
    vector<Point> pointsAll;
    // iterate through each defect
    for(int i=0;i<newDefects.size();i++){
        // get the starting point of the defect
        Point ptStart(contours[newDefects[i][0]]);
        // get the ending point of the defect
        Point ptEnd(contours[newDefects[i][1]]);
        // add the starting point to list of all points
        pointsAll.push_back(ptStart);
        // add the ending point to list of all points
        pointsAll.push_back(ptEnd);
    }
    // boolean flag to indicate if current point has no close points in the list of filtered points
    bool flag = false;
    // iterate through all the points
    for(int i=0;i<pointsAll.size();i++)
    {
        // if list of filtered points have no previous points
        if(pointsFinal.size() == 0)
        {
            // add the point to list of filtered points
            pointsFinal.push_back(pointsAll[i]);
        }
        // if the list of filtered points already some points
        else
        {
            // set flag to indicate that there is no close points
            flag = false;
            // iterate through all filtered points
            for(int j = 0;j<pointsFinal.size();j++)
            {
                // check if the distance is within threshold
                if(distanceP2P(pointsFinal[j],pointsAll[i])<SystemConfiguration::rpd_thresh)
                {
                    // mark this point as close point
                    flag = true;
                    break;
                }
            }
            // if the point is not close point
            if(flag == false)
            {
                // add to list of filtered points
                pointsFinal.push_back(pointsAll[i]);
            }
        }
    }
    // return list of filtered points
    return pointsFinal;
}

Mat ImageProcessor::getSkin(Mat input)
{
    //------------------------------------------------------
    // detect skin by color range
    //------------------------------------------------------
    // matrix to hold filtered image
    Mat skin;
    // convert the color scale to YCrCb scale from BGR scale
    cvtColor(input,skin,COLOR_BGR2YCrCb);
    // filter by predefined color constrant
    inRange(skin,Scalar(SystemConfiguration::y_min,SystemConfiguration::cr_min,SystemConfiguration::cb_min),Scalar(SystemConfiguration::y_max,SystemConfiguration::cr_max,SystemConfiguration::cb_max),skin);
    // return the filtered image
    return skin;
}

void ImageProcessor::generateMouseEvents()
{
    //------------------------------------------------------
    // generate mouse events, 3 type of events are available
    // single click , double click, click-hold
    //------------------------------------------------------
    // check if any mouse pointer available
    if(pointerManager.isPointerAvailable())
    {
        // reset the reset counter because we got a frame
        framesWithResetCounter = 0;
        // get the active filtered point
        Point activeFilteredPoint = pointerManager.getFilteredPointer();
        // check if the active point is in mouse ROI
        if(activeFilteredPoint.x >= SystemConfiguration::topX &&
                activeFilteredPoint.x <= SystemConfiguration::bottomX &&
                activeFilteredPoint.y >= SystemConfiguration::topY &&
                activeFilteredPoint.y <= SystemConfiguration::bottomY)
        {
            // convert X coordinate of active point to screen coordinate
            int XLoc = ((double)(activeFilteredPoint.x-SystemConfiguration::topX) / (double)(SystemConfiguration::bottomX - SystemConfiguration::topX)) * (double)widget.geometry().width();
            // convert Y coordinate of active point to screen coordinate
            int YLoc = ((double)(activeFilteredPoint.y-SystemConfiguration::topY) / (double)(SystemConfiguration::bottomY - SystemConfiguration::topY)) * (double)widget.geometry().height();

            // move the mouse pointer to the location
            mouseManager.mouseMove(XLoc , YLoc);

            // check if conditions met for activating single click
            if(finalPoints.size() >= 5 &&
                    !isMouseDown &&
                    framesWithMouseDownActivationCounter == 0 &&
                    !isDoubleClickActivated &&
                    framesWithDoubleClickActivationCounter == 0 )
            {
                // reset the deactivation counter for single click becuse activation is going to start
                framesWithClickDeactivationCounter = 0;
                // check if already single click is not activated to prevent continious single clicks
                if(!isClickActivated)
                {
                    // increment the single click activation counter
                    framesWithClickActivationCounter ++;
                    // check if the counter exceeds the event activation threshold
                    if(framesWithClickActivationCounter >= SystemConfiguration::fea_thresh)
                    {
                        // reset the single click activation counter
                        framesWithClickActivationCounter = 0;
                        // mark that single ckick is activated to prevent multiple clicks until its de activated
                        isClickActivated = true;
                        // generate the single click event
                        mouseManager.mouseEvent("click",1);
                    }
                }
            }
            // check if conditions met for activating double click
            else if(finalPoints.size() == 4 &&
                    !isMouseDown &&
                    framesWithMouseDownActivationCounter == 0 &&
                    !isClickActivated &&
                    framesWithClickActivationCounter == 0 )
            {
                // reset the deactivation counter for double click becuse activation is going to start
                framesWithDoubleClickDeactivationCounter = 0;
                // check if already double click is not activated to prevent continious double clicks
                if(!isDoubleClickActivated)
                {
                    // increment the double click activation counter
                    framesWithDoubleClickActivationCounter ++;
                    // check if the counter exceeds the event activation threshold
                    if(framesWithDoubleClickActivationCounter >= SystemConfiguration::fea_thresh)
                    {
                        // reset the double click activation counter
                        framesWithDoubleClickActivationCounter = 0;
                        // mark that double ckick is activated to prevent multiple double clicks until its de activated
                        isDoubleClickActivated = true;
                        // generate the double click event
                        mouseManager.mouseEvent("click,click",1);
                    }
                }
            }
            // check if conditions met for activating click and hold
            else if((finalPoints.size() == 2 || finalPoints.size() == 3) &&
                    !isDoubleClickActivated &&
                    framesWithDoubleClickActivationCounter == 0 &&
                    !isClickActivated &&
                    framesWithClickActivationCounter == 0 )
            {
                // reset the mouse down deactivation counter
                framesWithMouseDownDeactivationOunter = 0;
                // check if already mouse is not down
                if(!isMouseDown)
                {
                    // increment the mouse down activation counter
                    framesWithMouseDownActivationCounter ++;
                    // check if mouse down activation counter exceeds activation threshold
                    if(framesWithMouseDownActivationCounter >= SystemConfiguration::fea_thresh)
                    {
                        // reset the activation counter
                        framesWithMouseDownActivationCounter = 0;
                        // set the flag to precent from duplicate same events
                        isMouseDown = true;
                        // generate mouse down event
                        mouseManager.mouseEvent("mousedown",1);
                    }
                }
            }
            // check if single click is activated
            else if(isClickActivated)
            {
                // check if the single click deactivation counter exceeds the deactivation threshold
                if(framesWithClickDeactivationCounter >= SystemConfiguration::fed_thresh)
                {
                    // set flag to indicate that previous single click is deactivated and new single click is allowed
                    isClickActivated = false;
                }
                // deactivation counter do not exceed threshold
                else
                {
                    // increment the single click deactivation counter
                    framesWithClickDeactivationCounter ++;
                }
            }
            // check if double click is activated
            else if(isDoubleClickActivated)
            {
                // check if the double click deactivation counter exceeds the deactivation threshold
                if(framesWithDoubleClickDeactivationCounter >= SystemConfiguration::fed_thresh)
                {
                    // set flag to indicate that previous double click is deactivated and new double click is allowed
                    isDoubleClickActivated = false;
                }
                // deactivation counter do not exceed threshold
                else
                {
                    // increment the double click deactivation counter
                    framesWithDoubleClickDeactivationCounter ++;
                }
            }
            else if(isMouseDown)
            {
                // check if mouse down deactivation counter exceeds threshold
                if(framesWithMouseDownDeactivationOunter >= SystemConfiguration::fed_thresh)
                {
                    // set the flag to indicate that mouse is up
                    isMouseDown = false;
                    // generate the mouse up signal
                    mouseManager.mouseEvent("mouseup",1);
                }else
                {
                    // increment the mouse down deactivation counter
                    framesWithMouseDownDeactivationOunter ++;
                }
            }
            else if(!isClickActivated && framesWithClickActivationCounter > 0)
            {
                // check if the click deactivation counter exceeds the deactivation threshold
                if(framesWithClickDeactivationCounter >= SystemConfiguration::fed_thresh)
                {
                    // then reject the activation request by setting it to zero
                    framesWithClickActivationCounter = 0;
                }
                // click deactivation counter dosent exceeds the deactivation threshold
                else
                {
                    // increment the deactivation counter
                    framesWithClickDeactivationCounter ++;
                }
            }
            else if(!isDoubleClickActivated && framesWithDoubleClickActivationCounter > 0)
            {
                // check if the double click deactivation counter exceeds the deactivation threshold
                if(framesWithDoubleClickDeactivationCounter >= SystemConfiguration::fed_thresh)
                {
                    // then reject the activation request by setting it to zero
                    framesWithDoubleClickActivationCounter = 0;
                }
                // click deactivation counter dosent exceeds the deactivation threshold
                else
                {
                    // increment the deactivation counter
                    framesWithDoubleClickDeactivationCounter ++;
                }
            }
            else if(!isMouseDown && framesWithMouseDownActivationCounter > 0)
            {
                // check if mouse down deactivation counter exceeds threshold
                if(framesWithMouseDownDeactivationOunter >= SystemConfiguration::fed_thresh)
                {
                    // reset mouse down activation counter
                    framesWithMouseDownActivationCounter = 0;
                }
                // mouse down deactivation counter do not exceeds the threshold
                else
                {
                    // increment mouse down deactivation counter
                    framesWithMouseDownDeactivationOunter ++;
                }
            }
        }
        // points are out of bound
        else
        {
            // check if reset counter exceeds deactivation threshold
            if(framesWithResetCounter >= SystemConfiguration::fed_thresh)
            {
                // check if already mouse id down
                if(isMouseDown)
                {
                    // generate mouse up signal
                    mouseManager.mouseEvent("mouseup",1);
                }
                // reset flags
                isMouseDown = false;
                isClickActivated = false;
                isDoubleClickActivated = false;
                // reset counters
                framesWithDoubleClickActivationCounter = 0;
                framesWithDoubleClickDeactivationCounter = 0;
                framesWithMouseDownDeactivationOunter = 0;
                framesWithMouseDownActivationCounter = 0;
                framesWithClickDeactivationCounter = 0;
                framesWithClickDeactivationCounter = 0;
            }else
            {
                // increment the reset counter
                framesWithResetCounter ++;
            }
        }
    }

}
