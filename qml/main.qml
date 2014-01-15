/*
 * Copyright 2013 Yuuto Tokunaga
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
//import QtQuick.LocalStorage 2.0
import "components"

ApplicationWindow {
	id: mainWindow
	title: qsTr("Aztter")

	width: 360*dp
	height: 640*dp

	Component.onCompleted : {
		console.log("name: ", Screen.name)
		console.debug("width: ", Screen.width, " height: ", Screen.height)
		if(Screen.primaryOrientation === Qt.LandscapeOrientation){
			console.debug("LandScape")
		}
		else {
			console.debug("Portrait")
		}
		console.debug("pixelDensity: ", Screen.pixelDensity)
	}

	property Component loadingPage: LoadingPage { }
	property Component authPage: AuthPage { }
	property Component timelineContainer: TimelineContainer {
		onUpdateStatusBar: mainWindow.updateStatusBar(message)
	}

	function updateStatusBar(message) {
		statusLabel.text = message
		statusBarTimer.start()
	}

	Storage {
		id: storage
	}

	StackView {
		id: stackView

		anchors.fill: parent
		initialItem: loadingPage

		delegate: StackViewDelegate {
			pushTransition: StackViewTransition {
				PropertyAnimation {
					target: enterItem
					property: "x"
					duration: 500
					easing.type: Easing.OutQuad
					from: enterItem.width
					to: 0
				}
			}

			popTransition: StackViewTransition {
				PropertyAnimation {
					target: exitItem
					property: "x"
					duration: 500
					easing.type: Easing.InQuad
					from: 0
					to: enterItem.width
				}
			}

			replaceTransition: StackViewTransition {
				PropertyAnimation {
					target: enterItem
					property: "x"
					duration: 500
					easing.type: Easing.OutQuad
					from: enterItem.width
					to: 0
				}
				PropertyAnimation {
					target: exitItem
					property: "x"
					duration: 500
					easing.type: Easing.InQuad
					from: 0
					to: enterItem.width
				}
			}
		}
	}

	statusBar: StatusBar {
		width: parent.width
		height: statusLabel.text !== "" ? 25*dp : 0

		Behavior on height {
			NumberAnimation {
				easing.type: Easing.OutSine
			}
		}

		style: StatusBarStyle {
			background: Rectangle {
				implicitHeight: 30*dp
				implicitWidth: mainWindow.width
				color: "#2d373f"
				Rectangle {
					width: parent.width
					height: 2
					color: Qt.darker(parent.color, 1.5)
				}
			}
		}

		Label {
			id: statusLabel
			width: parent.width
			text: ""
			textFormat: Text.RichText
			onLinkActivated: Qt.openUrlExternally(link)
			wrapMode: Text.Wrap
			font.pointSize: 12
			font.bold: true
			color: "whitesmoke"
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
		}

		Timer {
			id: statusBarTimer
			interval: 10000
			running: false
			triggeredOnStart: false
			onTriggered: statusLabel.text = ""
		}
	}
}
