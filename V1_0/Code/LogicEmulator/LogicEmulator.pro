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
    userInterface/ioview.cpp \
    controller/xfeventdata.cpp \
    data/andgate.cpp \
    data/orgate.cpp \
    data/notgate.cpp

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
    userInterface/ioview.h \
    controller/xfeventdata.h \
    data/andgate.h \
    data/orgate.h \
    data/notgate.h

RESOURCES += \
    images.qrc
