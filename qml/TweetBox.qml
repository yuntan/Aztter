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
import QtQuick.Controls.Styles 1.1
import "components"

Item {
	id: box

	height: mainRow.height + 2.*mm

	function postTweet() {
		postButton.enabled = false;
		tweetEdit.enabled = false;
		aztter.tweet(tweetEdit.text);
	}

	Connections {
		target: aztter
		onPostStatusChanged: {
			switch(aztter.postStatus) {
			case aztter.Success:
				updateStatusBar(qsTr("Tweet sent."))
				break
			case aztter.RateLimitExceeded:
				updateStatusBar(qsTr("Rete limit exceeded."))
				break
			case aztter.OverCapacity:
				updateStatusBar(qsTr("Twitter is now over capacity."))
				break
			case aztter.InternalError:
				updateStatusBar(qsTr("Internal error occurd in twitter."))
				break
			case aztter.TimeInvalid:
				updateStatusBar(qsTr("Your computer's time is not valid. Please fix it."))
				break
			case aztter.Duplicate:
				updateStatusBar(qsTr("Tweet duplicated."))
				break
			default:
				updateStatusBar(qsTr("Unknown error."))
			}

			tweetEdit.text = ""
			postButton.enabled = false
			tweetEdit.enabled = true
		}
	}

	Rectangle {
		id: rect
		anchors.fill: parent
		color: "#c005b2d2"
		radius: height / 3
	}

	RowLayout {
		id: mainRow

		height: tweetEdit.height
		anchors {
			left: parent.left
			right: parent.right
			bottom: parent.bottom
			margins: 1.*mm
		}
		spacing: 1.*mm

		Button {
			id: openButton

			Layout.preferredWidth: parent.height
			Layout.fillHeight: true
			iconSource: "qrc:/img/star.png"
			style: ButtonStyle {
				background: Rectangle {
					width: control.width; height: control.height
					color: control.pressed ? "#80000000" : "transparent"
				}
			}
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

			Layout.preferredWidth: implicitWidth
			Layout.fillHeight: true

			enabled: false
			text: qsTr("Post")
			onClicked: postTweet()
		}
	}

//	FastBlur {
//		anchors.fill: rect
//		source: parent.parent
//		radius: 64
//	}
}
