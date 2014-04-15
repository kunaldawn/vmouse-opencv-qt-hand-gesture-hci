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
#include "CameraCapture.h"
#include "MatToQImageConverter.h"
#include <opencv2/opencv.hpp>
#include "SystemConfiguration.h"

using namespace cv;

CameraCapture::CameraCapture(VideoCapture capture) : QThread()
{
    captureDevice = capture;
}

void CameraCapture::run()
{
    while(1)
    {
        // create a matrix to store captured image
        Mat originalImageMat(SystemConfiguration::image_size ,SystemConfiguration::image_size,CV_8UC3);
        // check if capture is success
        if(captureDevice.read(originalImageMat))
        {
            // matrix to hold resized image
            Mat resizedImageMat = Mat::zeros(SystemConfiguration::image_size ,SystemConfiguration::image_size,CV_8UC3);
            // resize the captured image
            resize(originalImageMat,resizedImageMat,resizedImageMat.size(),0,0,INTER_NEAREST);
            // create display image
            QImage originalImage = convertMatToQImage(resizedImageMat);
            // get skin image
            Mat skinImageMat = processor.getSkin(resizedImageMat);
            // get processed images
            vector<Mat> processedImageMat = processor.getprocessedImage(skinImageMat);
            // create display image
            QImage frameQImage1 = convertMatToQImage(processedImageMat[0]);
            // create display image
            QImage frameQImage2 = convertMatToQImage(processedImageMat[1]);
            // get output image
            Mat justOutput = processor.getOutputImage();
            // create display image
            QImage frameQImage3 = convertMatToQImage(justOutput);
            // generate mouse events
            processor.generateMouseEvents();
            // generate events
            emit(capturedNewFrame(originalImage,frameQImage1,frameQImage2,frameQImage3));
        }
    }
}
