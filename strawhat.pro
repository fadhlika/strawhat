#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T09:19:40
#
#-------------------------------------------------

QT       += core gui charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = strawhat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotwindow.cpp

HEADERS  += mainwindow.h \
    plotwindow.h

FORMS    += mainwindow.ui \
    plotwindow.ui

RC_ICONS += app.ico
