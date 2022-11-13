QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    AutoProcess/autodriveprocess.cpp \
    AutoProcess/autodriveprocessmanager.cpp \
    AutoProcess/automineprocess.cpp \
    AutoProcess/automineprocessmanager.cpp \
    AutoProcess/autorunprocess.cpp \
    AutoProcess/autorunprocessmanager.cpp \
    AutoProcess/autotools.cpp \
    AutoProcess/autotrackprocess.cpp \
    AutoProcess/autotrackprocessmanager.cpp \
    globalshortcuthandler.cpp \
    keypushbutton.cpp \
    main.cpp \
    mainwindow.cpp \
    presetswitchwidget.cpp \
    toolshitdurationsdialog.cpp

HEADERS += \
    AutoProcess/autodriveprocess.h \
    AutoProcess/autodriveprocessmanager.h \
    AutoProcess/automineprocess.h \
    AutoProcess/automineprocessmanager.h \
    AutoProcess/autorunprocess.h \
    AutoProcess/autorunprocessmanager.h \
    AutoProcess/autotools.h \
    AutoProcess/autotrackprocess.h \
    AutoProcess/autotrackprocessmanager.h \
    globalshortcuthandler.h \
    keypushbutton.h \
    mainwindow.h \
    presetswitchwidget.h \
    toolshitdurationsdialog.h

FORMS += \
    mainwindow.ui \
    presetswitchwidget.ui \
    toolshitdurationsdialog.ui

CONFIG(release, debug|release):TARGET = 7Auto
CONFIG(debug, debug|release):TARGET = 7Autod

CONFIG(release, debug|release):LIBS += -L$$OUT_PWD/lib/ -lqxtGlobalShorcut
CONFIG(debug, debug|release):LIBS += -L$$OUT_PWD/lib/ -lqxtGlobalShorcutd

INCLUDEPATH += $$OUT_PWD/lib/
DEPENDPATH += $$OUT_PWD/lib/

CONFIG(release, debug|release):PRE_TARGETDEPS += $$OUT_PWD/lib/qxtGlobalShorcut.lib
CONFIG(debug, debug|release):PRE_TARGETDEPS += $$OUT_PWD/lib/qxtGlobalShorcutd.lib

LIBS += -luser32

RESOURCES += \
    7Auto.qrc

RC_FILE += \
    resource.rc
