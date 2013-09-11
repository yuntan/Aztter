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

import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import "aztterplugin" 1.0

ListView {
    id: homeTLView

    function loadStart() {
        helper.startFetching();
    }
    function loadStop() {
        helper.streamDisconnect();
    }

    clip: true
    Component.onCompleted: helper.startFetching()

    AztterHomeTLHelper {
        id: helper
        onTweetReceived: listModel.prepend(tweet)
        onTweetDeleted: listModel.remove(tweetId)
        onFavChanged: listModel.changeFav(tweetId, fav)
    }

    AztterTweetListModel {
        id: listModel
    }

    model: listModel
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
        onItemSwipedRight: helper.rt(tweetText, userScreenName)
        onClicked: console.log("tweetItem clicked!")
        onProfileIconClicked: console.log("profileIcon clicked!")
    }
}
