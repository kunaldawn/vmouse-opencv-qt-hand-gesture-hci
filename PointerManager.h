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
#ifndef POINTERMANAGER_H
#define POINTERMANAGER_H
#include <QObject>
#include <opencv2/opencv.hpp>

using namespace cv;

class PointerManager : public QObject
{
    Q_OBJECT
private:

    KalmanFilter kalmanFilter;
    Point currentPointer;
    Point previousPointer;
    Mat_<float> measurement;
    Point indexPoint;
    int framesWithoutPoints;
    bool isPointerActive;

public:
    PointerManager();
    void updateFrameData(vector<Point>);
    Point getTopMostPoint(vector<Point>);
    bool isInMagnetArea(Point, Point);
    bool isPointerAvailable();
    Point getActivePointer();
    Point getFilteredPointer();
};

#endif // POINTERMANAGER_H
