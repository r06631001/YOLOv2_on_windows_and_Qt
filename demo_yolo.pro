#-------------------------------------------------
#
# Project created by QtCreator 2017-10-16T11:49:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo_yolo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += C:\\opencv3.2.0_x64_vc2015\\include \
                C:\\opencv3.2.0_x64_vc2015\\include\\opencv \
                C:\\opencv3.2.0_x64_vc2015\\include\\opencv2 \

LIBS +=  C:\\opencv3.2.0_x64_vc2015\\lib\\opencv_world320.lib \
         C:\\opencv3.2.0_x64_vc2015\\lib\\opencv_world320d.lib \

INCLUDEPATH += C:\\yolov2_x64_vc2015\\src\

LIBS +=   C:\yolov2_x64_vc2015\lib_dll\\yolo_cpp_dll.lib \


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
