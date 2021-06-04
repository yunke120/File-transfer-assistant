QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/exe
TARGET = severapp


SOURCES += \
    main.cpp \
    tcpsever.cpp

HEADERS += \
    tcpsever.h

FORMS += \
    tcpsever.ui

