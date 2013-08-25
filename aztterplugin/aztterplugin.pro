TEMPLATE = lib
CONFIG += qt plugin
QT += qml network

DESTDIR +=  ../lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

TARGET = AztterPlugin

LIBS += \
	-L../lib
	-lqtweetlib

HEADERS += \
    aztteroauth.h \
    aztterplugin.h

SOURCES += \
    aztteroauth.cpp \
    aztterplugin.cpp
