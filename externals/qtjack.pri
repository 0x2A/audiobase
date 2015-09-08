INCLUDEPATH += \
    $$PWD/qtjack

CONFIG += no_keywords

QMAKE_CFLAGS = -fpermissive
QMAKE_CXXFLAGS = -fpermissive
QMAKE_LFLAGS = -fpermissive

SOURCES += \
    $$PWD/qtjack/system.cpp \
    $$PWD/qtjack/buffer.cpp \
    $$PWD/qtjack/client.cpp \
    $$PWD/qtjack/driver.cpp \
    $$PWD/qtjack/parameter.cpp \
    $$PWD/qtjack/port.cpp \
    $$PWD/qtjack/server.cpp \
    $$PWD/qtjack/audioport.cpp \
    $$PWD/qtjack/midiport.cpp \
    $$PWD/qtjack/audiobuffer.cpp \
    $$PWD/qtjack/midibuffer.cpp

HEADERS += \
    $$PWD/qtjack/system.h \
    $$PWD/qtjack/System \
    $$PWD/qtjack/Buffer \
    $$PWD/qtjack/buffer.h \
    $$PWD/qtjack/Client \
    $$PWD/qtjack/client.h \
    $$PWD/qtjack/Driver \
    $$PWD/qtjack/driver.h \
    $$PWD/qtjack/Parameter \
    $$PWD/qtjack/parameter.h \
    $$PWD/qtjack/Port \
    $$PWD/qtjack/port.h \
    $$PWD/qtjack/Server \
    $$PWD/qtjack/server.h \
    $$PWD/qtjack/processor.h \
    $$PWD/qtjack/Processor \
    $$PWD/qtjack/ringbuffer.h \
    $$PWD/qtjack/RingBuffer \
    $$PWD/qtjack/audioport.h \
    $$PWD/qtjack/AudioPort \
    $$PWD/qtjack/midiport.h \
    $$PWD/qtjack/audiobuffer.h \
    $$PWD/qtjack/midibuffer.h \
    $$PWD/qtjack/AudioBuffer \
    $$PWD/qtjack/MidiBuffer \
    $$PWD/qtjack/global.h \
    $$PWD/qtjack/MidiPort

OTHER_FILES = \
   $$PWD/qtjack/README.md \
   $$PWD/qtjack/LICENSE

LIBS += -ljack -ljackserver
