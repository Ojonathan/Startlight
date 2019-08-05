#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T19:55:31
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = starlight
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    metier_abs/crystal.cpp \
    metier_abs/dest.cpp \
    metier_abs/lens.cpp \
    metier_abs/nuke.cpp \
    metier_abs/point.cpp \
    metier_abs/ray.cpp \
    metier_abs/source.cpp \
    metier_abs/wall.cpp \
    gameview.cpp \
    o_sdo/sujetdobservation.cpp \
    metier_abs/level.cpp \
    metier_abs/mirror.cpp \
    metier_abs/objectStar.cpp \
    generateur.cpp

HEADERS  += mainwindow.h \
    metier_abs/crystal.h \
    metier_abs/dest.h \
    metier_abs/lens.h \
    metier_abs/nuke.h \
    metier_abs/point.h \
    metier_abs/ray.h \
    metier_abs/source.h \
    metier_abs/wall.h \
    gameview.h \
    o_sdo/observateur.h \
    o_sdo/sujetdobservation.h \
    metier_abs/level.h \
    metier_abs/mirror.h \
    metier_abs/objectStar.h \
    generateur.h

FORMS    += mainwindow.ui \
    generateur.ui

OTHER_FILES +=

RESOURCES += \
    images.qrc
