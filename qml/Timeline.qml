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
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

ScrollView {
	flickableItem.interactive: true
	flickableItem.flickableDirection: Flickable.VerticalFlick

	ListView {
		id: homeTLView

		property real mm: Screen.pixelDensity

		function loadStart() {
			aztter.startFetching()
		}
		function loadStop() {
			aztter.streamDisconnect()
		}

		clip: true
		Component.onCompleted: {
			loadStart()
		}

		Connections {
			target: aztter
			onFriendsListReceived: updateStatusBar(qsTr("Stream fetching started"))
			onTweetReceived: tweetListModel.prepend(tweet)
			onTweetDeleted: tweetListModel.remove(tweetId)
			onFavChanged: tweetListModel.changeFav(tweetId, fav)
		}

		model: tweetListModel
		delegate: TweetItem {
			text: tweetText
			createdAt: tweetCreatedAt
			fav: tweetFavorited
			name: userName
			screenName: "@" + userScreenName
			iconSource: userProfileImageUrl
			verified: userVerified
			isRT: rt
			rtName: rtUserName + " retweeted"
			rtIconSource: rtUserProfileImageUrl !== undefined ?
							  rtUserProfileImageUrl : ""

			//		onItemSwipedLeft: fav ? helper.unfav(tweetId) : helper.fav(tweetId)
			//		onItemSwipedRight: helper.rt(tweetId)
			onClicked: console.log("tweetItem clicked!")
			onSwiped: console.log("tweetItem swiped!")
			onProfileIconClicked: console.log("profileIcon clicked!")
		}

		// animation
		add: Transition {
			id: addTrans
			//		YAnimator { // sometimes Segmentation fault. BUG?
			//			from: addTrans.ViewTransition.destination.y
			//				  - addTrans.ViewTransition.item.height
			//			duration: 333
			//		}
			NumberAnimation {
				property: "y"
				from: addTrans.ViewTransition.destination.y
					  - addTrans.ViewTransition.item.height
				duration: 333
			}
			//		OpacityAnimator { //nothing changed. Why?
			//			from: 0.0; to: 1.0
			//			duration: 333
			//		}
			NumberAnimation {
				property: "opacity"
				from: 0.0; to: 1.0
				duration: 333
			}

			onRunningChanged: {
				if(running === false) { addTrans.ViewTransition.item.opacity = 1.0 }
			}
		}

		displaced: Transition {
			//		YAnimator {
			//			duration: 333
			//		}
			NumberAnimation {
				property: "y"
				duration: 333
			}
		}

		remove: Transition {
			id: remTrans
			//		YAnimator { // sometimes Segmentation fault. BUG?
			//			to: remTrans.ViewTransition.item.y
			//				- remTrans.ViewTransition.item.height
			//			duration: 333
			//		}
			NumberAnimation {
				property: "y"
				to: remTrans.ViewTransition.item.y
					- remTrans.ViewTransition.item.height
				duration: 333
			}
			//		OpacityAnimator { //nothing changed. Why?
			//			to: 0.0
			//			duration: 333
			//		}
			NumberAnimation {
				property: "opacity"
				to: 0.0
				duration: 333
			}

			onRunningChanged: {
				if(running === false) { remTrans.ViewTransition.item.opacity = 0.0 }
			}
		}
	}

	style: ScrollViewStyle {
		minimumHandleLength: 8*mm
		transientScrollBars: true
	}
}
