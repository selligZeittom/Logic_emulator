#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T15:34:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogicEmulator
TEMPLATE = app


SOURCES += main.cpp\
    data/data.cpp \
    data/gate.cpp \
    data/pin.cpp \
    data/portdata.cpp \
    userInterface/portui.cpp \
    controller/controller.cpp \
    XF/xf.cpp \
    XF/xfevent.cpp \
    XF/xftimer.cpp \
    controller/portcontroller.cpp \
    interfaces/iviewupdate.cpp \
    interfaces/idataupdate.cpp \
    factory.cpp \
    interfaces/icontrollerdata.cpp \
    userInterface/ioview.cpp

HEADERS  += \
    data/data.h \
    data/gate.h \
    data/pin.h \
    data/portdata.h \
    userInterface/portui.h \
    controller/controller.h \
    XF/ism.h \
    XF/xf.h \
    XF/xfevent.h \
    XF/xftimer.h \
    controller/portcontroller.h \
    interfaces/iviewupdate.h \
    interfaces/idataupdate.h \
    factory.h \
    interfaces/icontrollerdata.h \
    globalvariables.h \
    userInterface/ioview.h

RESOURCES += \
    images.qrc
