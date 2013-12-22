import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1

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

	color: mainColor

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

		RowLayout {
			anchors.fill: parent
			spacing: 3*mm

			// Back arrow button
			Rectangle {
				id: backButton

				Layout.preferredWidth: 10*mm
				Layout.fillHeight: true
				enabled: page.Stack.index > 1
				color: Qt.darker(titleColor, 1.2)
				Image {
					anchors.fill: parent
					anchors.margins: 1*mm
					source: "qrc:/img/aztter64.png"
					fillMode: Image.PreserveAspectFit
				}
				// push feedback
				Rectangle {
					anchors.fill: parent
					color: mouseBack.pressed ? "#40000000" : "transparent"
				}
				MouseArea {
					id: mouseBack
					anchors.fill: parent

					onClicked: page.back()
				}
			}

			Rectangle {
				id: titleLabelRect

				Layout.preferredWidth: titleLabel.width
				Layout.fillWidth: true
				color: mouseMenu.pressed ? "#40000000" : "transparent"
				Label {
					id: titleLabel

					anchors {
						verticalCenter: parent.verticalCenter
						left: parent.left
					}

					color: "whitesmoke"
					font.pointSize: 21
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
				Layout.preferredWidth: titleBarItem.implicitWidth
				Layout.fillHeight: true
				Item {
					id: titleBarItem

					anchors {
						fill: parent
						topMargin: 1*mm
						bottomMargin: 1*mm
						rightMargin: 3*mm
					}
				}
			}
		}
	}

	//bottom border line of titleBar
	Rectangle {
		id: titleBarLine
		anchors.top: titleBar.bottom
		width: parent.width; height: 1*mm
		color: Qt.darker(titleColor, 1.6)
	}

	// shadow of titleBar
	Rectangle {
		id:	titleBarShadow

		z:10
		width: parent.width; height: 5
		anchors.top: titleBarLine.bottom

		gradient: Gradient {
			GradientStop {position: 0; color: "#80000000"}
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

		anchors {
			top: titleBarLine.bottom
			bottom: parent.bottom
			left: parent.left
			right: parent.right
		}
	}
}
