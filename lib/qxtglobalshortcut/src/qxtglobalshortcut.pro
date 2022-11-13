QT  += core

TEMPLATE = lib
DEFINES += QXTGLOBALSHORTCUT_LIBRARY

CONFIG += c++17

CONFIG(release, debug|release):TARGET = qxtGlobalShorcut
CONFIG(debug, debug|release):TARGET = qxtGlobalShorcutd
CONFIG(debug, debug|release):TARGET = qxtGlobalShorcutd

SOURCES += \
    qxtglobalshortcut.cpp \
    qxtglobalshortcut_win.cpp

HEADERS += \
    qxtglobalshortcut.h \
    qxtglobalshortcut_p.h

msvc: LIBS += -luser32
