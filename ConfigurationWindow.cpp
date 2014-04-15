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
#include "ConfigurationWindow.h"
#include "ui_ConfigurationWindow.h"
#include "SystemConfiguration.h"

ConfigurationWindow::ConfigurationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigurationWindow)
{
    ui->setupUi(this);

    ui->in_image_size->setValue(SystemConfiguration::image_size);
    ui->in_y_min->setValue(SystemConfiguration::y_min);
    ui->in_y_max->setValue(SystemConfiguration::y_max);
    ui->in_cb_min->setValue(SystemConfiguration::cb_min);
    ui->in_cb_max->setValue(SystemConfiguration::cb_max);
    ui->in_cr_min->setValue(SystemConfiguration::cr_min);
    ui->in_cr_max->setValue(SystemConfiguration::cr_max);

    ui->val_image_size->setText(QString::number(SystemConfiguration::image_size));
    ui->val_y_min->setText(QString::number(SystemConfiguration::y_min));
    ui->val_y_max->setText(QString::number(SystemConfiguration::y_max));
    ui->val_cb_min->setText(QString::number(SystemConfiguration::cb_min));
    ui->val_cb_max->setText(QString::number(SystemConfiguration::cb_max));
    ui->val_cr_min->setText(QString::number(SystemConfiguration::cr_min));
    ui->val_cr_max->setText(QString::number(SystemConfiguration::cr_max));

    ui->in_open_kernel->setValue(SystemConfiguration::opening_kernel_size);
    ui->in_close_kernel->setValue(SystemConfiguration::closing_kernel_size);
    ui->in_blur_kernel->setValue(SystemConfiguration::blur_kernel_size);
    ui->in_blur_sigma->setValue(SystemConfiguration::blur_sigma * 100.0);
    ui->in_image_thresh->setValue(SystemConfiguration::image_threshold);

    ui->val_open_kernel->setText(QString::number(SystemConfiguration::opening_kernel_size));
    ui->val_close_kernel->setText(QString::number(SystemConfiguration::closing_kernel_size));
    ui->val_blur_kernel->setText(QString::number(SystemConfiguration::blur_kernel_size));
    ui->val_blur_sigma->setText(QString::number(SystemConfiguration::blur_sigma));
    ui->val_image_thresh->setText(QString::number(SystemConfiguration::image_threshold));

    ui->in_area_thresh->setValue(SystemConfiguration::area_thresh);
    ui->in_dp_epsilon->setValue(SystemConfiguration::dp_epsilon);

    ui->val_area_thresh->setText(QString::number(SystemConfiguration::area_thresh));
    ui->val_dp_epsilon->setText(QString::number(SystemConfiguration::dp_epsilon));

    ui->in_dt_max->setValue(SystemConfiguration::dt_max);
    ui->in_dt_min->setValue(SystemConfiguration::dt_min);
    ui->in_at_max->setValue(SystemConfiguration::at_max);
    ui->in_at_min->setValue(SystemConfiguration::at_min);
    ui->in_rh_thresh->setValue(SystemConfiguration::rh_thresh * 100.0);
    ui->in_rpd_thresh->setValue(SystemConfiguration::rpd_thresh);

    ui->val_dt_max->setText(QString::number(SystemConfiguration::dt_max));
    ui->val_dt_min->setText(QString::number(SystemConfiguration::dt_min));
    ui->val_at_max->setText(QString::number(SystemConfiguration::at_max));
    ui->val_at_min->setText(QString::number(SystemConfiguration::at_min));
    ui->val_rh_thresh->setText(QString::number(SystemConfiguration::rh_thresh));
    ui->val_rpd_thresh->setText(QString::number(SystemConfiguration::rpd_thresh));

    ui->in_fm_radius->setValue(SystemConfiguration::fm_radius);
    ui->in_kf_noise->setValue(SystemConfiguration::kf_noise * 10000.0);
    ui->in_fwp_th->setValue(SystemConfiguration::fwp_thresh);
    ui->in_fea_th->setValue(SystemConfiguration::fea_thresh);
    ui->in_fed_th->setValue(SystemConfiguration::fed_thresh);
    ui->in_tx->setValue(SystemConfiguration::topX);
    ui->in_ty->setValue(SystemConfiguration::topY);
    ui->in_bx->setValue(SystemConfiguration::bottomX);
    ui->in_by->setValue(SystemConfiguration::bottomY);

    ui->val_fm_radius->setText(QString::number(SystemConfiguration::fm_radius));
    ui->val_kf_noise->setText(QString::number(SystemConfiguration::kf_noise));
    ui->val_fwp_th->setText(QString::number(SystemConfiguration::fwp_thresh));
    ui->val_fea_th->setText(QString::number(SystemConfiguration::fea_thresh));
    ui->val_fed_th->setText(QString::number(SystemConfiguration::fed_thresh));
    ui->val_tx->setText(QString::number(SystemConfiguration::topX));
    ui->val_ty->setText(QString::number(SystemConfiguration::topY));
    ui->val_bx->setText(QString::number(SystemConfiguration::bottomX));
    ui->val_by->setText(QString::number(SystemConfiguration::bottomY));

}

ConfigurationWindow::~ConfigurationWindow()
{
    delete ui;
}

void ConfigurationWindow::on_in_image_size_valueChanged(int value)
{
    SystemConfiguration::image_size = value;
    ui->val_image_size->setText(QString::number(SystemConfiguration::image_size));
}

void ConfigurationWindow::on_in_y_min_valueChanged(int value)
{
    SystemConfiguration::y_min = value;
    ui->val_y_min->setText(QString::number(SystemConfiguration::y_min));
}

void ConfigurationWindow::on_in_y_max_valueChanged(int value)
{
    SystemConfiguration::y_max = value;
    ui->val_y_max->setText(QString::number(SystemConfiguration::y_max));
}

void ConfigurationWindow::on_in_cb_min_valueChanged(int value)
{
    SystemConfiguration::cb_min = value;
    ui->val_cb_min->setText(QString::number(SystemConfiguration::cb_min));
}

void ConfigurationWindow::on_in_cb_max_valueChanged(int value)
{
    SystemConfiguration::cb_max = value;
    ui->val_cb_max->setText(QString::number(SystemConfiguration::cb_max));
}

void ConfigurationWindow::on_in_cr_min_valueChanged(int value)
{
    SystemConfiguration::cr_min = value;
    ui->val_cr_min->setText(QString::number(SystemConfiguration::cr_min));
}

void ConfigurationWindow::on_in_cr_max_valueChanged(int value)
{
    SystemConfiguration::cr_max = value;
    ui->val_cr_max->setText(QString::number(SystemConfiguration::cr_max));
}

void ConfigurationWindow::on_in_open_kernel_valueChanged(int value)
{
    SystemConfiguration::opening_kernel_size = value;
    ui->val_open_kernel->setText(QString::number(SystemConfiguration::opening_kernel_size));
}

void ConfigurationWindow::on_in_close_kernel_valueChanged(int value)
{
    SystemConfiguration::closing_kernel_size = value;
    ui->val_close_kernel->setText(QString::number(SystemConfiguration::closing_kernel_size));
}

void ConfigurationWindow::on_in_blur_kernel_valueChanged(int value)
{
    if(value % 2 == 1)
    {
        SystemConfiguration::blur_kernel_size = value;
        ui->val_blur_kernel->setText(QString::number(SystemConfiguration::blur_kernel_size));
    }
}

void ConfigurationWindow::on_in_blur_sigma_valueChanged(int value)
{
    SystemConfiguration::blur_sigma = value / 100.0;
    ui->val_blur_sigma->setText(QString::number(SystemConfiguration::blur_sigma));
}

void ConfigurationWindow::on_in_image_thresh_valueChanged(int value)
{
    SystemConfiguration::image_threshold = value;
    ui->val_image_thresh->setText(QString::number(SystemConfiguration::image_threshold));
}


void ConfigurationWindow::on_in_area_thresh_valueChanged(int value)
{
    SystemConfiguration::area_thresh = value;
    ui->val_area_thresh->setText(QString::number(SystemConfiguration::area_thresh));
}

void ConfigurationWindow::on_in_dp_epsilon_valueChanged(int value)
{
    SystemConfiguration::dp_epsilon = value;
    ui->val_dp_epsilon->setText(QString::number(SystemConfiguration::dp_epsilon));
}

void ConfigurationWindow::on_in_dt_min_valueChanged(int value)
{
    SystemConfiguration::dt_min = value;
    ui->val_dt_min->setText(QString::number(SystemConfiguration::dt_min));
}

void ConfigurationWindow::on_in_dt_max_valueChanged(int value)
{
    SystemConfiguration::dt_max = value;
    ui->val_dt_max->setText(QString::number(SystemConfiguration::dt_max));
}

void ConfigurationWindow::on_in_at_min_valueChanged(int value)
{
    SystemConfiguration::at_min = value;
    ui->val_at_min->setText(QString::number(SystemConfiguration::at_min));
}

void ConfigurationWindow::on_in_at_max_valueChanged(int value)
{
    SystemConfiguration::at_max = value;
    ui->val_at_max->setText(QString::number(SystemConfiguration::at_max));
}

void ConfigurationWindow::on_in_rh_thresh_valueChanged(int value)
{
    SystemConfiguration::rh_thresh = value / 100.0;
    ui->val_rh_thresh->setText(QString::number(SystemConfiguration::rh_thresh));
}

void ConfigurationWindow::on_in_rpd_thresh_valueChanged(int value)
{
    SystemConfiguration::rpd_thresh = value;
    ui->val_rpd_thresh->setText(QString::number(SystemConfiguration::rpd_thresh));
}

void ConfigurationWindow::on_in_fm_radius_valueChanged(int value)
{
    SystemConfiguration::fm_radius = value;
    ui->val_fm_radius->setText(QString::number(SystemConfiguration::fm_radius));
}

void ConfigurationWindow::on_in_kf_noise_valueChanged(int value)
{
    SystemConfiguration::kf_noise = value / 10000.0;
    ui->val_kf_noise->setText(QString::number(SystemConfiguration::kf_noise));
}

void ConfigurationWindow::on_in_fwp_th_valueChanged(int value)
{
    SystemConfiguration::fwp_thresh = value;
    ui->val_fwp_th->setText(QString::number(SystemConfiguration::fwp_thresh));
}

void ConfigurationWindow::on_in_fea_th_valueChanged(int value)
{
    SystemConfiguration::fea_thresh = value;
    ui->val_fea_th->setText(QString::number(SystemConfiguration::fea_thresh));
}

void ConfigurationWindow::on_in_fed_th_valueChanged(int value)
{
    SystemConfiguration::fed_thresh = value;
    ui->val_fed_th->setText(QString::number(SystemConfiguration::fed_thresh));
}

void ConfigurationWindow::on_pushButton_clicked()
{
    SystemConfiguration config;
    config.saveSettings();
}

void ConfigurationWindow::on_in_tx_valueChanged(int value)
{
    SystemConfiguration::topX = value;
    ui->val_tx->setText(QString::number(SystemConfiguration::topX));
}

void ConfigurationWindow::on_in_ty_valueChanged(int value)
{
    SystemConfiguration::topY = value;
    ui->val_ty->setText(QString::number(SystemConfiguration::topY));
}

void ConfigurationWindow::on_in_bx_valueChanged(int value)
{
    SystemConfiguration::bottomX = value;
    ui->val_bx->setText(QString::number(SystemConfiguration::bottomX));
}

void ConfigurationWindow::on_in_by_valueChanged(int value)
{
    SystemConfiguration::bottomY = value;
    ui->val_by->setText(QString::number(SystemConfiguration::bottomY));
}
