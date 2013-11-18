TARGET = aztter
TEMPLATE = app

SOURCES += main.cpp

OTHER_FILES += qml/aztterplugin/qmldir
qmldir.files = qml/aztterplugin/qmldir

# Add more folders to ship with the application, here
qmlfolder.source = qml
qmlfolder.target = ./
imgfolder.source = img
imgfolder.target = ./
libfolder.source = aztterplugin/lib
libfolder.target = ./
DEPLOYMENTFOLDERS = \
	qmlfolder \
	imgfolder \
	libfolder

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
