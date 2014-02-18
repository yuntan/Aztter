TARGET = aztter
TEMPLATE = app

QT += qml quick widgets network twitterapi sql
android : QT += androidextras

SOURCES += \
    main.cpp \
    src/unionmodel.cpp

HEADERS += \
    src/unionmodel.h \
    src/aztterkeystore.h

QML_FILES += \
    qml/components/Card.qml \
    qml/components/FlatButton.qml \
    qml/components/Page.qml \
    qml/AuthPage.qml \
    qml/Empty.qml \
    qml/LoadingPage.qml \
    qml/main.qml \
    qml/Storage.qml \
    qml/TimelineContainer.qml \
    qml/TweetBox.qml \
    qml/TweetItem.qml \
    qml/components/Shape.qml

JS_FILES += \
    js/Utils.js

OTHER_FILES += $$QML_FILES $$JS_FILES android/AndroidManifest.xml

RESOURCES += \
    qml/qml.qrc \
    img/img.qrc \
    js/js.qrc

OBJECTS_DIR = tmp
MOC_DIR = tmp
INC_DIR = KQOAuth/include

QMAKE_CXXFLAGS += -std=c++0x

ANDROID_EXTRA_LIBS =

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
