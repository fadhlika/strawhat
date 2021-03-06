#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T09:19:40
#
#-------------------------------------------------

QT       += charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = strawhat
TEMPLATE = app
CONFIG += static
QMAKE_CXXFLAGS += -Os
SOURCES += main.cpp\
        mainwindow.cpp \
    plotwindow.cpp \
    settingwindow.cpp

HEADERS  += mainwindow.h \
    plotwindow.h \
    version.h \
    settingwindow.h

FORMS    += mainwindow.ui \
    plotwindow.ui \
    settingwindow.ui

RC_ICONS += app.ico

RC_FILE += \
    resource.rc
