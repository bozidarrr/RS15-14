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
    GUI/unetiosobu.cpp \
    engine/porodicnostablo.cpp \
    GUI/dialognovaosoba.cpp \
    GUI/widgetosoba.cpp \
    GUI/okvirstabla.cpp \
    alati/filterobject.cpp \
    alati/filterzalabelu.cpp \
    GUI/widgetrelacija.cpp \
    GUI/glavniprozor.cpp \
    engine/dete.cpp \
    engine/brak.cpp

HEADERS  += \
    alati/datum.h \
    engine/osoba.h \
    GUI/unetiosobu.h \
    engine/porodicnostablo.h \
    GUI/dialognovaosoba.h \
    GUI/widgetosoba.h \
    GUI/okvirstabla.h \
    alati/filterobject.h \
    alati/filterzalabelu.h \
    GUI/widgetrelacija.h \
    GUI/glavniprozor.h \
    engine/dete.h \
    engine/brak.h

FORMS    += unetiosobu.ui \
    widgetosoba.ui \
    dialognovaosoba.ui \
    GUI/okvirstabla.ui \
    widgetrelacija.ui \
    glavniprozor.ui

RESOURCES += \
    slike.qrc

OTHER_FILES +=
