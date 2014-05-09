//----------------------------------------------------------------------
// VMouse - OpenCV Virtual Mouse (HCI)
// Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>
// Copyright (C) 2014  Medha Devaraj <medha.devaraj@gmail.com>
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QThread>
#include <QImage>
#include "CameraCapture.h"
#include "ConfigurationWindow.h"
#include <QProcess>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void startAutoMode(int devId);
    ~MainWindow();
    
private slots:
    // a slot to receive start button click signal
    void on_startBtn_clicked();
    // slot to receive all the images for display
    void updateCameraFeedDisplay(QImage, QImage, QImage, QImage);
    // slot to receive configure button click signal
    void on_btn_configure_clicked();

private:
    Ui::MainWindow *ui;
    // id of the camera to be used
    int cameraId;
    // device for geting camera feed
    VideoCapture captureDevice;
    // function to start processing
    void startProcessing();
    // camera capture object
    CameraCapture *cameraCapture;
    // config window object
    ConfigurationWindow *configWindow;
};

#endif // MAINWINDOW_H
