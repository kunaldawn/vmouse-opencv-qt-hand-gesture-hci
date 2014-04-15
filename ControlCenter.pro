#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T09:55:46
#
#-------------------------------------------------

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
