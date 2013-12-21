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

	width: 360
	height: 640

	property real mm: Screen.pixelDensity

	Component.onCompleted : {
		console.log("name: ", Screen.name)
		console.debug("width: ", Screen.width, " height: ", Screen.height)
		if(Screen.primaryOrientation==Qt.LandscapeOrientation){
			console.debug("LandScape")
		}
		else{
			console.debug("Portrait")
		}
		console.debug("pixelDensity: ", Screen.pixelDensity)
	}

	property Component loadingPage: LoadingPage { }
	property Component authPage: AuthPage { }
	property Component timelineContainer: TimelineContainer { }

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
		opacity: statusLabel.text !== "" ? 1 : 0
		height: statusLabel.text !== "" ? units.gu(5) : 0

		Behavior on height {
			NumberAnimation {
				easing.type: Easing.OutSine
			}
		}

		style: StatusBarStyle {
			padding {
				left: 0
				right: 0
				top: 0
				bottom: 0
			}
			property Component background: Rectangle {
				implicitHeight: 65 * ApplicationInfo.ratio
				implicitWidth: root.width
				color: ApplicationInfo.colors.smokeGray
				Rectangle {
					width: parent.width
					height: 1
					color: Qt.darker(
							   parent.color, 1.5)
				}
				Rectangle {
					y: 1
					width: parent.width
					height: 1
					color: "white"
				}
			}
		}

		Label {
			id: statusLabel
		}
	}
}
