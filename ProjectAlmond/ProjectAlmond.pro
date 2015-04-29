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
    alati/datum.cpp \
    GUI/glavniprozor.cpp \
    engine/osoba.cpp \
    engine/supruznik.cpp \
    GUI/unetiosobu.cpp

HEADERS  += \
    alati/datum.h \
    engine/osoba.h \
    engine/relacija.h \
    engine/supruznik.h \
    GUI/glavniprozor.h \
    GUI/unetiosobu.h \
    GUI/WidgetDrag.h

FORMS    += glavniprozor.ui \
    unetiosobu.ui

RESOURCES += \
    slike.qrc
