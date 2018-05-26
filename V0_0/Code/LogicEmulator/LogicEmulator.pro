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
        mainwindow.cpp \
    data/data.cpp \
    data/gate.cpp \
    data/pin.cpp \
    data/portdata.cpp \
    userInterface/portui.cpp \
    interfaces/icontroller.cpp \
    controller/controller.cpp \
    XF/xf.cpp \
    XF/xfevent.cpp \
    XF/xftimer.cpp \
    controller/portcontroller.cpp \
    interfaces/iviewupdate.cpp \
    interfaces/idataupdate.cpp \
    userInterface/outputview.cpp \
    userInterface/inputview.cpp \
    factory.cpp \
    userInterface/view.cpp

HEADERS  += mainwindow.h \
    data/data.h \
    data/gate.h \
    data/pin.h \
    data/portdata.h \
    userInterface/portui.h \
    interfaces/icontroller.h \
    controller/controller.h \
    XF/ism.h \
    XF/xf.h \
    XF/xfevent.h \
    XF/xftimer.h \
    controller/portcontroller.h \
    interfaces/iviewupdate.h \
    interfaces/idataupdate.h \
    userInterface/outputview.h \
    userInterface/inputview.h \
    factory.h \
    userInterface/view.h

RESOURCES += \
    images.qrc
