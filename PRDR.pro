#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T16:38:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PRDR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stationcoord.cpp \
    global.cpp \
    satellite.cpp

HEADERS  += mainwindow.h \
    datatypes.h \
    stationcoord.h \
    global.h \
    satellite.h

FORMS    += mainwindow.ui

DISTFILES +=

include($$PWD\gsl\gsl.pri)
#DEFINES += GSL_DLL
#INCLUDEPATH += $$PWD\gsl\include
#LIBS += -L$$PWD\gsl\lib -llibgsl
#LIBS += -L$$PWD\gsl\lib -llibgslcblas
