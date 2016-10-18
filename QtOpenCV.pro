#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T22:17:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenCV
TEMPLATE = app


SOURCES += main.cpp\
        qcvwidget.cpp \
    opencvworker.cpp

HEADERS  += qcvwidget.h \
    opencvworker.h

FORMS    += qcvwidget.ui

INCLUDEPATH += C:\opencv\opencv530\install\include
LIBS += C:/opencv/opencv530/install/x86/mingw/bin/libopencv_core2413.dll
LIBS += C:/opencv/opencv530/install/x86/mingw/bin/libopencv_highgui2413.dll
LIBS += C:/opencv/opencv530/install/x86/mingw/bin/libopencv_imgproc2413.dll
LIBS += C:/opencv/opencv530/install/x86/mingw/bin/libopencv_video2413.dll
