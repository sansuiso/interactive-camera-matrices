#-------------------------------------------------
#
# Project created by QtCreator 2015-04-04T15:12:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraMatrices
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cameramatriceswidget.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    cameramatriceswidget.h \
    camera.h

macx:QMAKE_CXXFLAGS += -std=c++11
