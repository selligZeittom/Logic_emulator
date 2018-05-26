#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T22:49:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogicEmulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Data/gates.cpp \
    Data/pin.cpp \
    data/data.cpp \
    data/gate.cpp

HEADERS  += mainwindow.h \
    Data/gates.h \
    Data/pin.h \
    data/data.h \
    data/gate.h
