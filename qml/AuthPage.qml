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
//import QtWebKit 3.0
import "components"

Page {
	id: authPage

	title: qsTr("Twitter Authentication")
//	busy: authWebView.loading

	Component.onCompleted: {
		aztter.startAuth()
		busy = true
	}

	Connections {
		target: aztter
//		onAuthPageRequested: authWebViewl.url = authPageUrl
		onAuthPageRequested: {
			busy = false
			Qt.openUrlExternally(authPageUrl)
		}
		onAuthorized: stackView.push(timelineContainer)
	}

	Label {
		id: authLabel

		width: parent.width
		anchors.top: parent.top
		text: qsTr("Let's do twitter authentication first.")
		font.pointSize: 18
		color: "white"
	}


//	WebView {
//		id: authWebView
//		width: parent.width
//		anchors.top: authLabel.bottom
//		anchors.topMargin: parent.height / 20
//		anchors.bottom: parent.bottom
//	}

	TextField {
		id: authUrl
		width: parent.width * 4 / 5
		anchors {
			top: authLabel.bottom
			topMargin: parent.height / 20
			horizontalCenter: parent.horizontalCenter
		}
	}
}
