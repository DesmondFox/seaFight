#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T16:58:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = seaBattle
TEMPLATE = app
#QMAKE_CXXFLAGS_RELEASE += -MP4

SOURCES += \
    ai.cpp \
    field.cpp \
    fieldclass.cpp \
    indexesandstatus.cpp \
    kicks.cpp \
    main.cpp \
    processofgame.cpp \
    ship.cpp \
    startdialog.cpp \
    window.cpp \
    stat.cpp \
    about.cpp

HEADERS  += \
    ai.h \
    field.h \
    fieldclass.h \
    indexesandstatus.h \
    kicks.h \
    processofgame.h \
    ship.h \
    startdialog.h \
    window.h \
    stat.h \
    about.h

FORMS    +=

RESOURCES += \
    resourses.qrc


