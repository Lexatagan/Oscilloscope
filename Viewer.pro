#-------------------------------------------------
#
# Project created by QtCreator 2016-07-30T15:56:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Viewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        display.cpp \
    processor.cpp \
    displaywidget.cpp

HEADERS  += mainwindow.h \
        display.h \
    processor.h \
    displaywidget.h
