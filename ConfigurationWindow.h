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
#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConfigurationWindow;
}

class ConfigurationWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ConfigurationWindow(QWidget *parent = 0);
    ~ConfigurationWindow();
    
private slots:
    void on_in_image_size_valueChanged(int value);
    void on_in_y_min_valueChanged(int value);
    void on_in_y_max_valueChanged(int value);
    void on_in_cb_min_valueChanged(int value);
    void on_in_cb_max_valueChanged(int value);
    void on_in_cr_min_valueChanged(int value);
    void on_in_cr_max_valueChanged(int value);
    void on_in_open_kernel_valueChanged(int value);
    void on_in_close_kernel_valueChanged(int value);
    void on_in_blur_kernel_valueChanged(int value);
    void on_in_blur_sigma_valueChanged(int value);
    void on_in_image_thresh_valueChanged(int value);
    void on_in_area_thresh_valueChanged(int value);
    void on_in_dp_epsilon_valueChanged(int value);
    void on_in_dt_min_valueChanged(int value);
    void on_in_dt_max_valueChanged(int value);
    void on_in_at_min_valueChanged(int value);
    void on_in_at_max_valueChanged(int value);
    void on_in_rh_thresh_valueChanged(int value);
    void on_in_rpd_thresh_valueChanged(int value);
    void on_in_fm_radius_valueChanged(int value);
    void on_in_kf_noise_valueChanged(int value);
    void on_in_fwp_th_valueChanged(int value);
    void on_in_fea_th_valueChanged(int value);
    void on_in_fed_th_valueChanged(int value);
    void on_pushButton_clicked();
    void on_in_tx_valueChanged(int value);
    void on_in_ty_valueChanged(int value);
    void on_in_bx_valueChanged(int value);
    void on_in_by_valueChanged(int value);

private:
    Ui::ConfigurationWindow *ui;
};

#endif // CONFIGURATIONWINDOW_H
