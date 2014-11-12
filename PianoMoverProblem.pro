#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T16:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PianoMoverProblem
TEMPLATE = app

INCLUDEPATH += /user/include/
LIBS        += -L/usr/include/
LIBS        += -lCGAL
LIBS        += -lgmp
LIBS        += -lmpfr

QMAKE_CXXFLAGS += -frounding-math
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    sceneproblem.cpp

HEADERS  += mainwindow.h \
    sceneproblem.h

FORMS    += mainwindow.ui
