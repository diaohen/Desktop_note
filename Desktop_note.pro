#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T15:17:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Desktop_note
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp

HEADERS  += mainwindow.h \
    note.h

FORMS    += mainwindow.ui \
    note.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    image.qrc

