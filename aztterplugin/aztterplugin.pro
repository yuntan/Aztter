TEMPLATE = lib
TARGET = aztterplugin
#uri = com.ubuntu.developers.yuntan.aztter

CONFIG += qt plugin
QT += qml network

DESTDIR += lib
OBJECTS_DIR = tmp
MOC_DIR = tmp
INC_DIR = ../KQOAuth/include

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
	../KQOAuth/src \

# aztterplugin
HEADERS += \
	aztterplugin.h \
	aztterkeystore.h \
	y.h \
	e.h \
	k.h \
	aztterapibase.h \
	aztterstatusupdate.h \
	aztteruserstream.h \
	aztterhometlhelper.h \
	azttertweetlistmodel.h \
	azttertweetenum.h \
	aztterfav.h \
	aztterlocalstorage.h \
	aztterauthhelper.h \
	aztterrt.h \
	aztterhometl.h

SOURCES += \
	aztterplugin.cpp \
	aztterkeystore.cpp \
	aztterapibase.cpp \
	aztterstatusupdate.cpp \
	aztteruserstream.cpp \
	aztterhometlhelper.cpp \
	azttertweetlistmodel.cpp \
	aztterfav.cpp \
	aztterlocalstorage.cpp \
	aztterauthhelper.cpp \
	aztterrt.cpp \
	aztterhometl.cpp

# KQOAuth
PUBLIC_HEADERS += \
	../KQOAuth/src/kqoauthmanager.h \
	../KQOAuth/src/kqoauthrequest.h \
	../KQOAuth/src/kqoauthrequest_1.h \
	../KQOAuth/src/kqoauthrequest_xauth.h \
	../KQOAuth/src/kqoauthglobals.h

PRIVATE_HEADERS += \
	../KQOAuth/src/kqoauthrequest_p.h \
	../KQOAuth/src/kqoauthmanager_p.h \
	../KQOAuth/src/kqoauthauthreplyserver.h \
	../KQOAuth/src/kqoauthauthreplyserver_p.h \
	../KQOAuth/src/kqoauthutils.h \
	../KQOAuth/src/kqoauthrequest_xauth_p.h

HEADERS += \
	$$PUBLIC_HEADERS \
	$$PRIVATE_HEADERS

SOURCES += \
	../KQOAuth/src/kqoauthmanager.cpp \
	../KQOAuth/src/kqoauthrequest.cpp \
	../KQOAuth/src/kqoauthutils.cpp \
	../KQOAuth/src/kqoauthauthreplyserver.cpp \
	../KQOAuth/src/kqoauthrequest_1.cpp \
	../KQOAuth/src/kqoauthrequest_xauth.cpp

DEFINES += KQOAUTH
