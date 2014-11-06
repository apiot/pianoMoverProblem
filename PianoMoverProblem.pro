#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T16:58:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PianoMoverProblem
TEMPLATE = app

#C:\Program Files\CGAL-4.5\auxiliary\gmp\lib
INCLUDEPATH += /user/include/
LIBS        += -L/usr/include/
LIBS        += -lCGAL
LIBS        += -lgmp
LIBS        += -lmpfr
QMAKE_CXXFLAGS += -frounding-math -03

SOURCES += main.cpp\
        mainwindow.cpp \
    sceneproblem.cpp

HEADERS  += mainwindow.h \
    sceneproblem.h

FORMS    += mainwindow.ui
