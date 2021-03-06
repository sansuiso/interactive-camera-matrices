#-------------------------------------------------
#
# Project created by QtCreator 2015-04-04T15:12:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = CameraMatrices
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cameramatriceswidget.cpp \
    camera.cpp \
    extrinsiccontrolwidget.cpp \
    intrinsiccontrolwidget.cpp \
    slidingcontrolwidget.cpp \
    extrinsicmatrixmodel.cpp \
    intrinsicmatrixmodel.cpp \
    cameramatrixmodel.cpp \
    modelasset.cpp \
    modelassetsmanager.cpp \
    modelinstance.cpp

HEADERS  += mainwindow.h \
    cameramatriceswidget.h \
    camera.h \
    extrinsiccontrolwidget.h \
    intrinsiccontrolwidget.h \
    slidingcontrolwidget.h \
    extrinsicmatrixmodel.h \
    intrinsicmatrixmodel.h \
    cameramatrixmodel.h \
    modelasset.h \
    modelassetsmanager.h \
    modelinstance.h

macx:QMAKE_CXXFLAGS += -std=c++11

macx:INCLUDEPATH += /usr/local/include/eigen3

RESOURCES += \
    core-profile.qrc

DISTFILES += \
    simple.vert \
    simple.frag
