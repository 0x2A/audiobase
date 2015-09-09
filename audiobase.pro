#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T00:28:30
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = audiobase
TEMPLATE = app

CONFIG += c++11

MODULES += JACK


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/Audio/IAudioInterface.cpp \
    src/Audio/audioengine.cpp \
    src/Audio/channel.cpp \
    src/Audio/jackchannel.cpp \
    src/transport/track.cpp \
    src/transport/audiotrack.cpp \
    src/transport/miditrack.cpp \
    src/system/settings.cpp

HEADERS  += src/mainwindow.h \
    src/Audio/IAudioInterface.h \
    src/Audio/audioengine.h \
    src/Audio/aitypes.h \
    src/Audio/channel.h \
    src/Audio/jackchannel.h \
    src/transport/track.h \
    src/transport/audiotrack.h \
    src/transport/miditrack.h \
    src/system/settings.h \
    src/common.h

FORMS    += src/ui/mainwindow.ui

contains( MODULES, JACK) {
    message("adding module: JACK")

    DEFINES += USE_JACK
    include(externals/qtjack.pri)

    SOURCES += src/Audio/aijack.cpp
    HEADERS += src/Audio/aijack.h
}
