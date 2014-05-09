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
#ifndef SYSTEMCONFIGURATION_H
#define SYSTEMCONFIGURATION_H

class SystemConfiguration
{
public:
    SystemConfiguration();
    void loadDefaults();
    void saveSettings();
    void loadSettings();

    // skin detection settings
    static int y_min;
    static int y_max;
    static int cr_min;
    static int cr_max;
    static int cb_min;
    static int cb_max;
    static int image_size;

    // preprocessing settings
    static int opening_kernel_size;
    static int closing_kernel_size;
    static int blur_kernel_size;
    static double blur_sigma;
    static int image_threshold;

    // contour settings
    static int area_thresh;
    static int dp_epsilon;

    // elemination settings
    static int dt_min;
    static int dt_max;
    static int at_min;
    static int at_max;
    static double rh_thresh;
    static int rpd_thresh;

    // point management settings
    static int fm_radius;
    static double kf_noise;
    static int fwp_thresh;
    static int fea_thresh;
    static int fed_thresh;
    static int topX;
    static int topY;
    static int bottomX;
    static int bottomY;
};

#endif // SYSTEMCONFIGURATION_H
