Aztter for Ubuntu Phone
=======================

twitter client for Ubuntu Phone

# Build
※ if you can't build project though you do referencing it , sorry.

1. git clone
1. cd Aztter
1. git submodule init
1. git submodule update
1. cd kQOAuth
1. /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
1. make
1. cd ../aztterplugin
1. /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
1. make
1. cd ..
1. LD_LIBRARY_PATH=./lib qmlscene main.qml

