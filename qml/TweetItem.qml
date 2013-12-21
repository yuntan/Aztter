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
import "components"
import "twttr.js" as Twttr

Item {
	id: tweetItem

	property string tweet
	property string text
	property alias createdAt: timeLabel.createdAt
	property alias fav: favIndicator.fav
	property alias name: nameLabel.text
	property alias screenName: screenNameLabel.text
	property alias iconSource: iconImage.source
	property alias verified: verifiedIcon.verified
	property alias isRT: rtRow.isRT
	property alias rtName: rtNameLabel.text
	property alias rtIconSource: rtIconImage.source

	//	property alias control: controlContainer.control
	//	property bool __controlAreaPressed: false

	signal clicked()
	signal swiped(int index)
	signal profileIconClicked()

	Component.onCompleted: {
		textLabel.text = Twttr.autoLink(text)
	}

	width: parent.width; height: tweetCard.height + 2*mm

	clip: true

	//	onSwiped: {
	//		console.log("Item swiped. index: " + index)
	//		onSwiped(index)
	//	}

	//	backgroundIndicator: Item {
	//		anchors.fill: parent

	//		Rectangle {
	//			anchors.fill: parent
	//			color: "#DD4814"
	//		}

	//		Label {
	//			anchors {
	//				left: swipingState === "SwipingLeft" ? parent.left : undefined
	//				right: swipingState === "SwipingRight" ? parent.right : undefined
	//				verticalCenter: parent.verticalCenter
	//			}

	//			text: swipingState === "SwipingRight"
	//				  ? "Swipe to RT >|"
	//				  : "|< Swipe to Fav"
	//			maximumLineCount: 1
	//			color: "white"
	//			font.bold: true
	////			fontSize: "x-large"
	//		}
	//	}

	Card {
		id: tweetCard

		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
			margins: 2*mm
		}
		height: rtRect.height + mainRow.height + 3*mm

		onClicked: tweetItem.clicked()

		Rectangle {
			id: rtRect

			anchors {
				top: parent.top
				left: parent.left
				right: parent.right
			}
			height: isRT ? 6*mm : 0
			color: "#80000000"

			RowLayout {
				id: rtRow

				anchors {
					fill: parent
					margins: 0.5*mm
					leftMargin: 6*mm
				}

				spacing: 1*mm
				property bool isRT
				visible: isRT

				/*
				Image {
					id: rtImage

					Layout.preferredWidth: 4*mm
					sourceSize.width: 4*mm; sourceSize.height: 4*mm
					source: "qrc:/img/retweet.png"
					fillMode: Image.PreserveAspectFit
				} */

				Image {
					id: rtIconImage

					Layout.minimumWidth: 5*mm
					sourceSize.width: 5*mm; sourceSize.height: 5*mm
					fillMode: Image.PreserveAspectFit

					Component.onCompleted: {
						if(isRT && (source === undefined || source === ""))
							source = Qt.resolvedUrl("qrc:/img/loading.png")
					}
				}

				Label {
					id: rtNameLabel

					clip: true
					Layout.fillWidth: true
					maximumLineCount: 1
					elide: Text.ElideRight
					color: "#666666"
					font.bold: true
				}
			}
		}

		RowLayout {
			id: mainRow

			anchors {
				top: rtRect.bottom
				left: parent.left
				right: parent.right
				margins: 1*mm
			}
			height: textCol.height
			spacing: 1*mm

			Image {
				id: iconImage

				Layout.alignment: Qt.AlignTop
				Layout.minimumWidth: 12*mm
				sourceSize.width: 12*mm; sourceSize.height: 12*mm
				fillMode: Image.PreserveAspectFit

				property url fallbackSource: Qt.resolvedUrl("qrc:/img/loading.png")

				Component.onCompleted: {
					if(source == undefined || source == "")
						source = fallbackSource
				}
			}

			ColumnLayout {
				id: textCol

				anchors.top: parent.top
				Layout.fillWidth: true
				spacing: 1*mm

				RowLayout {
					id: nameRow

					Layout.preferredHeight: nameLabel.font.pixelSize
					spacing: 0.5*mm

					Label {
						id: nameLabel

						maximumLineCount: 1
						elide: Text.ElideRight
						color: "#666666"
						font.bold: true
					}

					Image {
						id: verifiedIcon
						property bool verified

						visible: verified
						Layout.preferredWidth: verified ? parent.height : 0
						sourceSize.width: parent.height
						sourceSize.height: parent.height
						source: "qrc:/img/verified.png"
					}

					Item {
						Layout.minimumWidth: 1*mm
					}

					Label {
						id: screenNameLabel
						Layout.fillWidth: true

						//		fontSize: "small"
						maximumLineCount: 1
						elide: Text.ElideRight
						color: "#666666"
					}

					Item {
						Layout.fillWidth: true
					}

					Image {
						id: favIndicator
						property bool fav

						visible: fav
						Layout.preferredWidth: fav ? parent.height : 0
						sourceSize.width: parent.height
						sourceSize.height: parent.height
						source: "qrc:/img/star.png"
					}
				}

				Label {
					id: textLabel

					clip: true
					//		fontSize: "medium"
					wrapMode: Text.Wrap
					elide: Text.ElideNone
					color: "#666666"
					textFormat: Text.StyledText
					onLinkActivated: {
						console.log(link + " link activated")
						Qt.openUrlExternally(link)
					}
				}

				Item {
					Layout.minimumHeight: 0.5*mm
				}

				Label {
					id: timeLabel

					property date createdAt

					Layout.preferredHeight: font.pointSize

					text: calcTime()

					//		fontSize: "small"
					elide: Text.ElideNone
					color: "#666666"

					function calcTime() {
						// FIXME
						var now = new Date();
						var diff = Math.floor((now.getTime() - createdAt.getTime()) / 1000);
						if(diff >= 86400)
							return Math.floor(diff / 86400) + qsTr(" days ago");
						if(diff >= 3600)
							return Math.floor(diff / 3600) + qsTr(" hours ago");
						if(diff >= 60)
							return Math.floor(diff / 60) + qsTr(" minutes ago");
						if(diff >= 10)
							return diff + qsTr(" seconds ago");
						return qsTr("Just now");
					}
				}
			}
		}
	}
}

/*
//		Item {
//			id: controlContainer
//			property Item control
//			// use the width of the control if there is (possibly elided) text,
//			// or full width available if there is no text.
//			anchors.fill: parent
//			onControlChanged: {
//				if (control) control.parent = controlContainer;
//			}

//		Connections {
//			target: tweetItem.__mouseArea

//			onClicked: {
////                console.debug(control)
//				if (__mouseArea.mouseX > profileIcon.x
//						&& __mouseArea.mouseX < profileIcon.x + profileIcon.width
//						&& __mouseArea.mouseY > profileIcon.y
//						&& __mouseArea.mouseY < profileIcon.y + profileIcon.height) {
//					profileIconClicked();
//				} else {
//					tweetItem.clicked();
//				}
//			}

//			onPressAndHold: {
////                if (control && control.enabled && __mouseArea.mouseX < progressionHelper.x && control.hasOwnProperty("pressAndHold")) {
//				if (control && control.enabled && control.hasOwnProperty("pressAndHold")) {
//					control.pressAndHold();
//				} else {
//					tweetItem.pressAndHold();
//				}
//			}
//		}
//		}
*/

