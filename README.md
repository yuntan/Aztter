Aztter (twitter client)
=======================

Twitter client for PC and android devices

To Build this software requires Qt5.2 and perl

# Build
## 1. Install twitter4qml

1. git clone https://github.com/yuntan/twitter4qml.git
1. cd twitter4qml
1. perl C:\\Qt\\5.2.0\\mingw48\_32\\bin\\syncqt.pl -version 0.1.0
1. qmake
1. make or mingw32-make
1. make install or mingw32-make install

## 2. Build Aztter

1. git clone https://github.com/yuntan/Aztter.git
1. cd Aztter
1. qmake
1. make
1. ./aztter

# Build for Android
## 1. Install twitter4qml

1. cd twitter4qml
1. perl C:\\Qt\\5.2.0\\mingw48\_32\\bin\\syncqt.pl -version 0.1.0
1. qmake -spec android-g++
1. make or mingw32-make
1. make install or mingw32-make install

(Open twitter4qml.pro with Qt Creator and build, then make install in build directory is easy way)

## 2. Build Aztter
Open aztter.pro with Qt Creator, select kit(android), and run.

# About this software
This software is distributed under the MIT License.

__The following are used__  
Qt5.2 LGPL  
twitter4qml  
UnionModel (from QNeptunea Project)

