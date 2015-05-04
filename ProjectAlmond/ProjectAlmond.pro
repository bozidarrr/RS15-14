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
    engine/osoba.cpp \
    engine/supruznik.cpp \
    GUI/unetiosobu.cpp \
    engine/porodicnostablo.cpp \
    engine/relacija.cpp \
    GUI/glavniprozor2.cpp \
    GUI/dialognovaosoba.cpp \
    GUI/widgetosoba.cpp \
    GUI/okvirstabla.cpp \
    alati/filterobject.cpp \
    alati/filterzalabelu.cpp

HEADERS  += \
    alati/datum.h \
    engine/osoba.h \
    engine/relacija.h \
    engine/supruznik.h \
    GUI/unetiosobu.h \
    GUI/WidgetDrag.h \
    engine/porodicnostablo.h \
    GUI/glavniprozor2.h \
    GUI/dialognovaosoba.h \
    GUI/widgetosoba.h \
    GUI/okvirstabla.h \
    alati/filterobject.h \
    alati/filterzalabelu.h

FORMS    += unetiosobu.ui \
    widgetosoba.ui \
    glavniprozor2.ui \
    dialognovaosoba.ui \
    GUI/okvirstabla.ui

RESOURCES += \
    slike.qrc

OTHER_FILES +=
