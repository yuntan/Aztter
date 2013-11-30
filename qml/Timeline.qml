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

ListView {
	id: homeTLView

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
		rtIconSource: rtUserProfileImageUrl
//        rtVerified: rtUserVerified

		onItemSwipedLeft: fav ? helper.unfav(tweetId) : helper.fav(tweetId)
		onItemSwipedRight: helper.rt(tweetId)
		onClicked: console.log("tweetItem clicked!")
		onProfileIconClicked: console.log("profileIcon clicked!")
	}

	// animation
	add: Transition {
		NumberAnimation {
			property: "x"
			from: units.gu(9); to: 0;
			duration: 333
		}
		NumberAnimation {
			property: "opacity"
			from: 0; to: 1.0;
			duration: 333
		}
	}

	displaced: Transition {
		NumberAnimation {
			properties: "x"
			to: 0
			duration: 333
		}
		NumberAnimation {
			properties: "y"
			duration: 333
		}
		NumberAnimation {
			properties: "opacity"
			to: 1.0
			duration: 333
		}
	}
}
