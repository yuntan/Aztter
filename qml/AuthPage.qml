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
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
//import QtWebKit 3.0
import "components"

Page {
	id: authPage
	title: qsTr("Twitter Authentication")

	property string authUrl

	Component.onCompleted: {
		aztter.startAuth()
	}

	Connections {
		target: aztter
		onAuthPageRequested: authUrl = authPageUrl
		onAuthorized: stackView.push(timelineContainer)
	}

	ColumnLayout {
		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
			margins: 25*dp
		}
		height: childrenRect.height
		spacing: 40*dp

		Label {
			id: authLabel

			Layout.fillWidth: true
			Layout.preferredHeight: implicitHeight
			text: qsTr("Welcome to Aztter\n\n" +
					   "You aren't logged in.\n" +
					   "Let's do twitter authentication.\n" +
					   "Please tap \"Open auth page\" button, and " +
					   "you will see Twitter authentication page.\n" +
					   "Please allow access from this app.")

			font.pointSize: 18
			color: "white"
			horizontalAlignment: Text.AlignHCenter
			wrapMode: Text.Wrap
		}

		// Qt5.2 Mobile dosen't supprt WebView
		//	WebView {
		//		id: authWebView
		//		width: parent.width
		//		anchors.top: authLabel.bottom
		//		anchors.topMargin: parent.height / 20
		//		anchors.bottom: parent.bottom
		//	}

		FlatButton {
			Layout.alignment: Qt.AlignHCenter
			Layout.fillWidth: true
			Layout.preferredHeight: implicitHeight
			fontPixelSize: 27*dp
			text: qsTr("Open auth page")
			onClicked: Qt.openUrlExternally(authUrl)
		}
	}
}
