#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T00:28:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = audiobase
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/Audio/IAudioInterface.cpp

HEADERS  += src/mainwindow.h \
    src/Audio/IAudioInterface.h

FORMS    += src/ui/mainwindow.ui
