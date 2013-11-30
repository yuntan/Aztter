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

import QtQuick 2.1
import QtQuick.Controls 1.0
//import QtQuick.LocalStorage 2.0
import "components"

ApplicationWindow {
	id: mainWindow
	title: qsTr("Aztter")

	width: 360
	height: 640

	Storage {
		id: storage
	}

	StackView {
		id: stackView

		anchors.fill: parent
		initialItem: loadingPage
//		initialItem: apage

		delegate: StackViewDelegate {
			property Component pushTransition: StackViewTransition {
				PropertyAnimation {
					target: enterItem
					property: "x"
					duration: 500
					easing.type: Easing.OutQuad
					from: enterItem.width ;to: 0

				}
			}

			property Component popTransition: StackViewTransition {
				PropertyAnimation {
					target: exitItem
					property: "x"
					duration: 500
					easing.type: Easing.InQuad
					from:0 ;to: enterItem.width
				}
			}
		}
	}

	Component {
		id: loadingPage
		LoadingPage {}
	}

	Component {
		id: authPage
		AuthPage {}
	}

	Component {
		id: timelineContainer
		TimelineContainer {}
	}

	Component {
		id: apage
		Page {title: "Page"; busy: true}
	}
}
