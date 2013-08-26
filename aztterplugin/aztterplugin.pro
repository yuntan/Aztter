TEMPLATE = lib
CONFIG += qt plugin
QT += qml network

INCLUDEPATH += ../QTweetLib/src

DESTDIR += ../lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

TARGET = AztterPlugin

LIBS += \
	-L../lib \
	-lqtweetlib

HEADERS += \
	aztterplugin.h \
	aztteroauth.h

SOURCES += \
	aztterplugin.cpp \
	aztteroauth.cpp
