TEMPLATE = lib
CONFIG += qt plugin
QT += qml network

DESTDIR += ../lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

QMAKE_CXXFLAGS += -std=c++0x

TARGET = AztterPlugin

INCLUDEPATH += ../kQOAuth/src

LIBS += \
	-L../lib \
	-lkqoauth

HEADERS += \
	aztterplugin.h \
	aztteroauth.h \
	aztterkeystore.h \
	y.h \
	e.h \
	k.h \
	aztterinit.h \
	aztterapibase.h \
	aztterstatusupdate.h \
	aztteruserstream.h \
    aztterhometlhelper.h \
    azttertweetlistmodel.h \
    azttertweetenum.h \
    aztterloadingpagehelper.h

SOURCES += \
	aztterplugin.cpp \
	aztteroauth.cpp \
    aztterkeystore.cpp \
	aztterinit.cpp \
	aztterapibase.cpp \
	aztterstatusupdate.cpp \
	aztteruserstream.cpp \
    aztterhometlhelper.cpp \
    azttertweetlistmodel.cpp \
    aztterloadingpagehelper.cpp
