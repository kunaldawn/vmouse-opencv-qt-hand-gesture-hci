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
#include "SystemConfiguration.h"
#include "QSettings"
#include "QFileInfo"
#include "iostream"

using namespace std;

int SystemConfiguration::y_min;
int SystemConfiguration::y_max;
int SystemConfiguration::cr_min;
int SystemConfiguration::cr_max;
int SystemConfiguration::cb_min;
int SystemConfiguration::cb_max;
int SystemConfiguration::image_size;

int SystemConfiguration::opening_kernel_size;
int SystemConfiguration::closing_kernel_size;
int SystemConfiguration::blur_kernel_size;
double SystemConfiguration::blur_sigma;
int SystemConfiguration::image_threshold;

int SystemConfiguration::area_thresh;
int SystemConfiguration::dp_epsilon;

int SystemConfiguration::dt_min;
int SystemConfiguration::dt_max;
int SystemConfiguration::at_min;
int SystemConfiguration::at_max;
double SystemConfiguration::rh_thresh;
int SystemConfiguration::rpd_thresh;

int SystemConfiguration::fm_radius;
double SystemConfiguration::kf_noise;
int SystemConfiguration::fwp_thresh;
int SystemConfiguration::fea_thresh;
int SystemConfiguration::fed_thresh;

int SystemConfiguration::topX;
int SystemConfiguration::topY;
int SystemConfiguration::bottomX;
int SystemConfiguration::bottomY;

SystemConfiguration::SystemConfiguration()
{

}

void SystemConfiguration::loadDefaults()
{
    y_min  = 0;
    y_max  = 255;
    cr_min = 133;
    cr_max = 173;
    cb_min = 77;
    cb_max = 127;
    image_size = 400;

    opening_kernel_size = 9;
    closing_kernel_size = 9;
    blur_kernel_size = 3;
    blur_sigma = 0.8;
    image_threshold = 10;

    area_thresh = 5000;
    dp_epsilon = 10;

    dt_min = 10;
    dt_max = 180;
    at_min = 15;
    at_max = 95;
    rh_thresh = 0.66;
    rpd_thresh = 30;

    fm_radius = 20;
    kf_noise = 0.001;
    fwp_thresh = 10;
    fea_thresh = 8;
    fed_thresh = 5;

    topX = 0;
    topY = 0;
    bottomX = image_size;
    bottomY = image_size;
}

void SystemConfiguration::saveSettings()
{
    QSettings settings("settings.conf",QSettings::IniFormat);

    settings.beginGroup("SKIN_DETECTION");
    settings.setValue("Y_MIN",y_min);
    settings.setValue("Y_MAX",y_max);
    settings.setValue("CB_MIN",cb_min);
    settings.setValue("CB_MAX",cb_max);
    settings.setValue("CR_MIN",cr_min);
    settings.setValue("CR_MAX",cr_max);
    settings.setValue("IMAGE_SIZE",image_size);
    settings.endGroup();

    settings.beginGroup("PRE_PROCESSING");
    settings.setValue("OPEN_KERNEL_SIZE",opening_kernel_size);
    settings.setValue("CLOSE_KERNEL_SIZE",closing_kernel_size);
    settings.setValue("BLUR_KERNEL_SIZE",blur_kernel_size);
    settings.setValue("BLUR_SIGMA",blur_sigma);
    settings.setValue("IMAGE_THRESHOLD",image_threshold);
    settings.endGroup();

    settings.beginGroup("CONTOUR_DETECTION");
    settings.setValue("AREA_THRESHOLD",area_thresh);
    settings.setValue("RAMER_DOGLAS_PEUCKER_EPSILON",dp_epsilon);
    settings.endGroup();

    settings.beginGroup("DEFECT_ELEMINATION");
    settings.setValue("DISTANCE_TOLERANCE_MAXIMUM",dt_max);
    settings.setValue("DISTANCE_TOLERANCE_MINIMUM",dt_min);
    settings.setValue("ANGLE_TOLERANCE_MAXIMUM",at_max);
    settings.setValue("ANGLE_TOLERANCE_MINIMUM",at_min);
    settings.setValue("REGION_HEIGHT_THRESHOLD",rh_thresh);
    settings.setValue("REDUNDENT_POINT_DISTANCE_THRESHOLD",rpd_thresh);
    settings.endGroup();

    settings.beginGroup("MOUSE_EVENT_GENERATION");
    settings.setValue("FINGER_MAGNET_RADIUS",fm_radius);
    settings.setValue("KALMAN_FILTER_NOISE",kf_noise);
    settings.setValue("FRAMES_WITHOUT_POINTS_THRESHOLD",fwp_thresh);
    settings.setValue("FRAME_EVENT_ACTIVATION_THRESHOLD",fea_thresh);
    settings.setValue("FRAME_EVENT_DEACTIVATION_THRESHOLD",fed_thresh);
    settings.setValue("ROI_TOP_X",topX);
    settings.setValue("ROI_TOP_Y",topX);
    settings.setValue("ROI_BOTTOM_X",bottomX);
    settings.setValue("ROI_BOTTOM_Y",bottomY);
    settings.endGroup();

    settings.sync();
}

void SystemConfiguration::loadSettings()
{
    bool configExist = QFileInfo("settings.conf").exists();
    if(configExist)
    {
        QSettings settings("settings.conf",QSettings::IniFormat);
        settings.beginGroup("SKIN_DETECTION");
        y_min = settings.value("Y_MIN").toInt();
        y_max = settings.value("Y_MAX").toInt();
        cb_min = settings.value("CB_MIN").toInt();
        cb_max = settings.value("CB_MAX").toInt();
        cr_min = settings.value("CR_MIN").toInt();
        cr_max = settings.value("CR_MAX").toInt();
        image_size = settings.value("IMAGE_SIZE").toInt();
        settings.endGroup();

        settings.beginGroup("PRE_PROCESSING");
        opening_kernel_size = settings.value("OPEN_KERNEL_SIZE").toInt();
        closing_kernel_size = settings.value("CLOSE_KERNEL_SIZE").toInt();
        blur_kernel_size = settings.value("BLUR_KERNEL_SIZE").toInt();
        blur_sigma = settings.value("BLUR_SIGMA").toDouble();
        image_threshold = settings.value("IMAGE_THRESHOLD").toInt();
        settings.endGroup();

        settings.beginGroup("CONTOUR_DETECTION");
        area_thresh= settings.value("AREA_THRESHOLD").toInt();
        dp_epsilon= settings.value("RAMER_DOGLAS_PEUCKER_EPSILON").toInt();
        settings.endGroup();

        settings.beginGroup("DEFECT_ELEMINATION");
        dt_max= settings.value("DISTANCE_TOLERANCE_MAXIMUM").toInt();
        dt_min= settings.value("DISTANCE_TOLERANCE_MINIMUM").toInt();
        at_max= settings.value("ANGLE_TOLERANCE_MAXIMUM").toInt();
        at_min= settings.value("ANGLE_TOLERANCE_MINIMUM").toInt();
        rh_thresh= settings.value("REGION_HEIGHT_THRESHOLD").toDouble();
        rpd_thresh= settings.value("REDUNDENT_POINT_DISTANCE_THRESHOLD").toInt();
        settings.endGroup();

        settings.beginGroup("MOUSE_EVENT_GENERATION");
        fm_radius= settings.value("FINGER_MAGNET_RADIUS").toInt();
        kf_noise= settings.value("KALMAN_FILTER_NOISE").toDouble();
        fwp_thresh= settings.value("FRAMES_WITHOUT_POINTS_THRESHOLD").toInt();
        fea_thresh= settings.value("FRAME_EVENT_ACTIVATION_THRESHOLD").toInt();
        fed_thresh= settings.value("FRAME_EVENT_DEACTIVATION_THRESHOLD").toInt();
        topX=settings.value("ROI_TOP_X").toInt();
        topY=settings.value("ROI_TOP_Y").toInt();
        bottomX=settings.value("ROI_BOTTOM_X").toInt();
        bottomY=settings.value("ROI_BOTTOM_Y").toInt();
        settings.endGroup();
    }else
    {
        loadDefaults();
        saveSettings();
    }

}


