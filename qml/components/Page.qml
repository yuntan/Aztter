import QtQuick 2.2
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
	signal titleIconClicked()
	signal titleLabelClicked()

	color: mainColor

	Rectangle {
		id: titleBar

		z:10 // so page contents doesn't draw on top
		anchors.top: parent.top
		width: parent.width
		height: 50*dp

		color: titleColor

		RowLayout {
			anchors.fill: parent
			spacing: 15*dp

			Rectangle {
				id: titleIconRect
				Layout.minimumWidth: parent.height
				Layout.fillHeight: true
//				enabled: page.Stack.index > 1
				color: Qt.darker(titleColor, 1.2)
				Image {
					id: titleIcon
					anchors.fill: parent
					anchors.margins: 5*dp
					source: "qrc:/img/aztter64.png"
					fillMode: Image.PreserveAspectFit
				}
				// push feedback
				Rectangle {
					anchors.fill: parent
					color: titleIconMouse.pressed ? "#40000000" : "transparent"
				}
				MouseArea {
					id: titleIconMouse
					anchors.fill: parent

					onClicked: page.titleIconClicked()
				}
			}

			Rectangle {
				id: titleLabelRect

				Layout.fillWidth: true
				Layout.fillHeight: true
				color: titleLabelMouse.pressed ? "#40000000" : "transparent"
				Label {
					id: titleLabel

					width: parent.width
					anchors {
						verticalCenter: parent.verticalCenter
						left: parent.left
					}

					color: "whitesmoke"
					font.pixelSize: 30*dp
					fontSizeMode: Text.HorizontalFit
					font.bold: true
				}
				MouseArea {
					id: titleLabelMouse
					anchors.fill: parent
					onClicked: page.titleLabelClicked()
				}
			}

			Item {
				Layout.preferredWidth: titleBarItem.implicitWidth
				Layout.fillHeight: true
				Item {
					id: titleBarItem

					anchors {
						fill: parent
						topMargin: 5*dp
						bottomMargin: 5*dp
						rightMargin: 15*dp
					}
				}
			}
		}
	}

	//bottom border line of titleBar
	Rectangle {
		id: titleBarLine
		anchors.top: titleBar.bottom
		width: parent.width; height: 3*dp
		color: Qt.darker(titleColor, 1.6)
	}

	// shadow of titleBar
	Rectangle {
		id:	titleBarShadow

		z:10
		width: parent.width; height: 5*dp
		anchors.top: titleBarLine.bottom

		gradient: Gradient {
			GradientStop {position: 0; color: "#80000000"}
			GradientStop {position: 1; color: "#00000000"}
		}
	}

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
