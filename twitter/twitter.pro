TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR +=  ../plugins
OBJECTS_DIR = tmp
MOC_DIR = tmp

TARGET = twitter

HEADERS += \
		twitter.h \
		oauth.h

SOURCES += \
		twitter.cpp \
		oauth.cpp