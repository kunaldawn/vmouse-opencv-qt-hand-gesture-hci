#----------------------------------------------------------------------
# VMouse - OpenCV Virtual Mouse (HCI)
# Copyright (C) 2014  Kunal Dawn <kunal.dawn@gmail.com>
# Copyright (C) 2014  Medha Devaraj <medha.devaraj@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#----------------------------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ControlCenter
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MatToQImageConverter.cpp \
    ImageProcessor.cpp \
    CameraCapture.cpp \
    PointerManager.cpp \
    MousePointerManager.cpp \
    ConfigurationWindow.cpp \
    SystemConfiguration.cpp

HEADERS  += MainWindow.h \
    MatToQImageConverter.h \
    ImageProcessor.h \
    CameraCapture.h \
    PointerManager.h \
    MousePointerManager.h \
    ConfigurationWindow.h \
    SystemConfiguration.h

FORMS    += MainWindow.ui \
    ConfigurationWindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += opencv

RESOURCES += \
    resources.qrc
