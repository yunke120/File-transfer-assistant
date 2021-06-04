QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/exe
TARGET = clientapp


SOURCES += \
    main.cpp \
    tcpclient.cpp

HEADERS += \
    tcpclient.h

FORMS += \
    tcpclient.ui


