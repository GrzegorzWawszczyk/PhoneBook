#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T15:53:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhoneBook_v2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    phonebookmodel.cpp \
    contactinfo.cpp \
    addcontact.cpp \
    editwindow.cpp

HEADERS  += mainwindow.h \
    phonebookmodel.h \
    contactinfo.h \
    addcontact.h \
    editwindow.h

FORMS    += mainwindow.ui \
    contactinfo.ui \
    addcontact.ui \
    editwindow.ui
