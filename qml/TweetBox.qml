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
//import QtGraphicalEffects 1.0
import "components"

Item {
	id: box

	height: mainRow.height + 2*mm

	function postTweet() {
		postButton.enabled = false;
		tweetEdit.enabled = false;
		aztter.tweet(tweetEdit.text);
	}

	Connections {
		target: aztter
		onPostStatusChanged: {
			//			if(aztter.postStatus === )
			tweetEdit.text = ""
			postButton.enabled = true
			tweetEdit.enabled = true
		}
	}

	Rectangle {
		id: rect
		anchors.fill: parent
		color: "#a005b2d2"
		radius: height / 3
	}

	RowLayout {
		id: mainRow

		height: tweetEdit.height
		anchors {
			left: parent.left
			right: parent.right
			bottom: parent.bottom
			margins: 1*mm
		}
		spacing: 2*mm

		FlatButton {
			id: openButton

			Layout.preferredWidth: parent.height
			Layout.fillHeight: true
			iconSource: "qrc:/img/star.png"
		}

		TextField {
			id: tweetEdit

			Layout.fillWidth: true

			font.pointSize: 18
			placeholderText: qsTr("What's happened?")

			Keys.onReturnPressed: {
				if(event.modifiers & Qt.ControlModifier || event.modifiers & Qt.ShiftModifier)
					postTweet();
				else
					event.accepted = false;
			}

			onTextChanged: {
				postButton.enabled = true;
				postButton.text = qsTr("Post")
				if(length >= 110){
					if(length > 140){
						postButton.enabled = false;
					} else if(length >= 130){
						// TODO: change color
					}
					postButton.text = 140 - length
				} else if(length == 0){
					postButton.enabled = false;
				}
			}
		}

		FlatButton {
			id: postButton

			Layout.preferredWidth: parent.height * 3 / 2
			Layout.fillHeight: true

			enabled: false
			text: qsTr("Post")
			textColor: "white"
			onClicked: postTweet()
		}
	}

//	FastBlur {
//		anchors.fill: rect
//		source: parent.parent
//		radius: 64
//	}
}
