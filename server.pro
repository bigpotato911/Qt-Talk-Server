#-------------------------------------------------
#
# Project created by QtCreator 2012-06-12T19:20:06
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tcpconnection.cpp \
    tcpthread.cpp \
    udpchat.cpp \
    tcpsocketserver.cpp \
    server.cpp \
    userdm.cpp \
    dbhelper.cpp \
    user.cpp

HEADERS += \
    tcpconnection.h \
    tcpthread.h \
    udpchat.h \
    tcpsocketserver.h \
    server.h \
    userdm.h \
    dbhelper.h \
    user.h
