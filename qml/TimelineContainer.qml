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
import TwitterAPI 1.1
import Aztter 1.0
import "components"
import "../js/Utils.js" as Utils

Page {
    id: timelineContainer
    title: qsTr("Timeline")

//	onTitleIconClicked: openMenu()
    onTitleLabelClicked: tlView.positionViewAtBeginning()

    UnionModel {
        id: homeTLModel
        UserStreamModel {
            id: userStream
            enabled: false
            onFollowedBy: {
                updateStatusBar(qsTr("You are followed by %1 (@%2)")
                                .arg(status.user.name).arg(status.user.screen_name)) }
            onFavorited: {
                updateStatusBar(qsTr("Your tweet is favorited by @%1")
                                .arg(status.user.screen_name)) }
            onUnfavorited: { updateStatusBar(qsTr("Your tweet is unfavorited by @%1")
                                             .arg(status.user.screen_name)) }
            onStreamingChanged: {
                if(streaming) { updateStatusBar(qsTr("Stream fetching started")) }
                else { updateStatusBar(qsTr("Stream fetching stopped")) }
            }
        }
        StatusesHomeTimelineModel {
            id: homeTL
            enabled: true
            count: 200
            pushOrder: StatusesHomeTimelineModel.PushAtOnce
            sortKey: "id_str"
            onLoadingChanged: {
                if(!loading) {
                    console.debug("HomeTimeline loaded")
                    userStream.enabled = true
                }
            }
        }
    }
    StatusesMentionsTimelineModel { id: mentionsTLModel; enabled: false}

    Status {
        id: twitter
        onFavoritedChanged: {
            if(favorited) { updateStatusBar(qsTr("Favorited")) }
            else { updateStatusBar(qsTr("Unfavorited")) }
        }
        onRetweetedChanged: {
            if(retweeted) { updateStatusBar(qsTr("Retweeted")) }
        }
    }

    ScrollView {
        anchors.fill: parent
        z: 1

        flickableItem.interactive: true
        flickableItem.flickableDirection: Flickable.VerticalFlick

        ListView {
            id: tlView

            model: homeTLModel

            delegate: TweetItem {
                isRT: model.retweeted_status !== undefined
                text: isRT ? model.retweeted_status.rich_text : model.rich_text
                createdAt: Utils.parseCreatedAt(isRT ? model.retweeted_status.created_at : model.created_at)
                fav: isRT ? model.retweeted_status.favorited : model.favorited
                name: isRT ? model.retweeted_status.user.name : model.user.name
                screenName: "@" + (isRT ? model.retweeted_status.user.screen_name : model.user.screen_name)
                iconSource: isRT ? model.retweeted_status.user.profile_image_url : model.user.profile_image_url
                verified: isRT ? model.retweeted_status.user.verified : model.user.verified
                rtName: model.user.name + " retweeted"
                rtIconSource: model.user.profile_image_url !== undefined ?
                                  model.user.profile_image_url : ""

                onClicked: console.debug("tweetItem clicked!")
                onProfileIconClicked: console.debug("profileIcon clicked!")
                onFlicked: {
                    console.debug("tweetItem flicked! index: %1".arg(index))
                    switch(index) {
                    case 1: // fav
                        twitter.id_str = model.id_str
                        twitter.favorite()
                        break
                    case 2: // RT
                        twitter.statusesRetweet({"id": model.id_str})
                        break
                    case 3: // favRT
                        twitter.id_str = model.id_str
                        twitter.favorite()
                        twitter.statusesRetweet({"id": model.id_str})
                    }
                }
            }

            // animation
            add: Transition {
                id: addTrans
//                YAnimator { // sometimes Segmentation fault. BUG?
//                    from: addTrans.ViewTransition.destination.y
//                          - addTrans.ViewTransition.item.height
//                    duration: 333
//                }
                NumberAnimation {
                    property: "y"
                    from: addTrans.ViewTransition.destination.y
                          - addTrans.ViewTransition.item.height
                    duration: 333
                }
            }

            displaced: Transition {
//                YAnimator {
//                    duration: 333
//                }
                NumberAnimation {
                    property: "y"
                    duration: 333
                }
            }

            remove: Transition {
                id: remTrans
//                YAnimator { // sometimes Segmentation fault. BUG?
//                    to: remTrans.ViewTransition.item.y
//                        - remTrans.ViewTransition.item.height
//                    duration: 333
//                }
                NumberAnimation {
                    property: "y"
                    to: remTrans.ViewTransition.item.y
                        - remTrans.ViewTransition.item.height
                    duration: 333
                }
            }

            transitions: [
                Transition {
                    NumberAnimation { properties: "opacity" }
                }
            ]
        }

        style: ScrollViewStyle {
            minimumHandleLength: 40*dp
            transientScrollBars: true
        }
    }

    TweetBox {
        id: tweetBox

        z: 2
        visible: true
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 5*dp
        }
    }

    Image {
        id: wallpaper

        z: 0
        anchors.fill: parent
        source: Qt.resolvedUrl("file:///C:/WorkSpace/wallpaper.jpg")
        fillMode: Image.PreserveAspectCrop
    }
}
