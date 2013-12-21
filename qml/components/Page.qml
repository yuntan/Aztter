import QtQuick 2.1
import QtQuick.Controls 1.0

Rectangle {
	id: page

	// ensure children added do not draw over the titleBar
	property alias data: main.data
	property alias title: titleLabel.text
	property alias titleBarContents: titleBarItem.data
	property color mainColor: "#56c4c3"
	property color titleColor: "#1ebba6"

	//modify statusBar's label
	signal updateStatusBar(string message)
	//back 1 page
	signal back()
	//open menu
	signal showMenu()
	color: "#1cbfac"


	/*
	// use container in order not titleBarShadow to be clipped
	// see http://stackoverflow.com/questions/15488714/how-to-create-drop-shadow-for-rectangle-on-qtquick-2-0
	Item {
		id: titleBarContainer

		z: 10
		visible: false
		width: parent.width
		height: 12*mm
	*/

	Rectangle {
		id: titleBar

		z:10 // so page contents doesn't draw on top
		anchors.top: parent.top
		width: parent.width
		height: 10*mm

		color: titleColor

		// Back arrow button
		Rectangle {
			id: backButton

			enabled: page.Stack.index !== 0
			width: 10*mm; height: parent.height
			anchors {
				top: parent.top
				left: parent.left
				bottom: parent.bottom
			}

			color: mouseBack.pressed ? "#40000000" : "transparent"

			Image {
				anchors.fill: parent
			}

			MouseArea {
				id: mouseBack
				anchors.fill: parent

				onClicked: page.back()
			}

			// white borderline
			Rectangle {
				width: 1; height: parent.height
				anchors.right: parent.right
				anchors.rightMargin: 1
				color: "white"
			}

			// right shadow
			Rectangle {
				width: 1; height: parent.height
				anchors.right: parent.right
				color: "#40000000"
			}
		}

		Rectangle {
			id: titleLabelRect

			implicitWidth: titleLabel.width
			anchors {
				top: parent.top
				bottom: parent.bottom
				left: backButton.right
				leftMargin: 3*mm
			}

			color: mouseMenu.pressed ? "#40000000" : "transparent"

			Label {
				id: titleLabel

				anchors {
					verticalCenter: parent.verticalCenter
					left: parent.left
				}

				color: "white"
				font.pixelSize: parent.height / 2
				fontSizeMode: Text.HorizontalFit
				font.bold: true
			}

			MouseArea {
				id: mouseMenu
				anchors.fill: parent
				onClicked: page.showMenu()
			}
		}


		Item {
			id: titleBarItem

			anchors {
				top: parent.top
				topMargin: 1*mm
				bottom: parent.bottom
				bottomMargin: 1*mm
				left:titleLabelRect.right
				leftMargin: 3*mm
				right: parent.right
				rightMargin: 3*mm
			}
		}

		//bottom border line of titleBar
		Rectangle {
			anchors.bottom: parent.bottom
			width: parent.width; height: 3
			color: Qt.darker(parent.color, 1.6)
		}
	}

	// shadow of titleBar
	Rectangle {
		id:	titleBarShadow

		width: parent.width; height: 5
		anchors.top: titleBar.bottom

		gradient: Gradient {
			GradientStop {position: 0; color: "#40000000"}
			GradientStop {position: 1; color: "#00000000"}
		}
	}

	/*
DropShadow {
	id: titleBarShadow

	z: 10
	anchors.fill: source

	horizontalOffset: 0
	verticalOffset: 1*mm
	radius: verticalOffset
	samples: radius * 2
	color: "#80000000"
	source: titleBarContainer
}
*/

	// main contents of	the page
	Item {
		id: main

		z:5
		anchors {
			top: titleBar.bottom
			bottom: parent.bottom
			left: parent.left
			right: parent.right
		}
	}
}
