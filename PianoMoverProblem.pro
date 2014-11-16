#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T16:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PianoMoverProblem
TEMPLATE = app

INCLUDEPATH += /user/local/include
LIBS        += -L"/usr/local/include"
LIBS        += -lCGAL
LIBS        += -lCGAL_Core
LIBS        += -lgmp
LIBS        += -lmpfr

QMAKE_CXXFLAGS += -frounding-math -O3


QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    sceneproblem.cpp \
    arrangement.cpp

HEADERS  += mainwindow.h \
    sceneproblem.h \
    arrangement.h

FORMS    += mainwindow.ui
