#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T23:54:38
#
#-------------------------------------------------

QT       += core gui widgets
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectAlmond
TEMPLATE = app


SOURCES += main.cpp\
        glavniprozor.cpp \
    datum.cpp \
    unetiosobu.cpp \
    supruznik.cpp \
    osoba.cpp

HEADERS  += glavniprozor.h \
    osoba.h \
    datum.h \
    unetiosobu.h \
    WidgetDrag.h \
    relacija.h \
    supruznik.h

FORMS    += glavniprozor.ui \
    unetiosobu.ui

RESOURCES += \
    slike.qrc
