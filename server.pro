#-------------------------------------------------
#
# Project created by QtCreator 2012-06-12T19:20:06
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    serverthread.cpp

HEADERS += \
    server.h \
    serverthread.h
