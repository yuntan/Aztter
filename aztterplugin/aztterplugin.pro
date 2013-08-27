TEMPLATE = lib
CONFIG += qt plugin
QT += qml network

DESTDIR += ../lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

TARGET = AztterPlugin

INCLUDEPATH += ../kQOAuth/src

LIBS += \
	-L../lib \
	-lkqoauth

HEADERS += \
	aztterplugin.h \
	aztteroauth.h

SOURCES += \
	aztterplugin.cpp \
	aztteroauth.cpp
