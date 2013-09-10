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
import "aztterplugin" 1.0

Empty {
    id: tweetItem

    property alias text: textLabel.text
    property alias createdAt: timeLabel.createdAt
    property alias fav: favIndicator.fav
    property alias name: nameLabel.text
    property alias screenName: screenNameLabel.text
    property alias iconSource: iconImage.source
    property alias verified: verifiedIcon.verified

    property alias control: controlContainer.control
    __acceptEvents: false
    property bool __controlAreaPressed: false

    signal profileIconClicked()

    width: parent.width
    height: Math.max(profileIcon.anchors.topMargin + profileIcon.height, nameLabel.anchors.topMargin + nameLabel.height + textLabel.height) + timeLabel.height + units.gu(1)

    draggable: true

    onItemSwipedLeft: {
        console.log("Item swiped to left");
        closeIndicator();
    }
    onItemSwipedRight: {
        console.log("Item swiped to right");
        closeIndicator();
    }

    Rectangle {
        id: controlHighlight

        visible: tweetItem.swipingState === "" ? control && __controlAreaPressed : false
        anchors.fill: parent
        color: Theme.palette.selected.base
    }

    UbuntuShape {
        id: profileIcon

        width: height
        height: units.gu(7)
        anchors {
            top: parent.top
            topMargin: units.gu(1)
            left: parent.left
            leftMargin: units.gu(1)
        }

        radius: "medium"
        image: Image {
            id: iconImage

            fillMode: Image.PreserveAspectCrop

            property url fallbackSource: Qt.resolvedUrl("Aztter80.png")

            Component.onCompleted: {
                if(source == undefined || source == "")
                    source = fallbackSource
            }
        }
    }

    Label {
        id: nameLabel

        clip: true
        anchors {
            top: parent.top
            topMargin: profileIcon.anchors.topMargin
            left: profileIcon.right
            leftMargin: units.gu(1)
        }

        maximumLineCount: 1
        elide: Text.ElideRight
        color: Theme.palette.normal.baseText
        font.bold: true
    }

    Image {
        id: verifiedIcon
        property bool verified

        width: verified ? height : 0
        height: nameLabel.height
        anchors {
            bottom: nameLabel.bottom
            left: nameLabel.right
        }

        source: verified ? "img/verified.png" : ""
        fillMode: Image.PreserveAspectCrop
    }

    Label {
        id: screenNameLabel

        clip: true
        width: {
            var w = parent.width - (profileIcon.anchors.leftMargin + profileIcon.width +
                                    nameLabel.anchors.leftMargin + nameLabel.width +
                                    verifiedIcon.width +
                                    screenNameLabel.anchors.leftMargin * 2 +
                                    favIndicator.width + favIndicator.anchors.rightMargin);
            return w > units.gu(2) ? w : 0;
        }
        anchors {
            left: verifiedIcon.right
            leftMargin: units.gu(1)
            bottom: nameLabel.bottom
        }

        fontSize: "small"
        maximumLineCount: 1
        elide: Text.ElideRight
        color: Theme.palette.normal.overlayText
    }

    Image {
        id: favIndicator
        property bool fav

        width: fav ? height : 0
        height: nameLabel.height
        anchors {
            bottom: nameLabel.bottom
            right: parent.right
            rightMargin: profileIcon.anchors.leftMargin
        }

        source: fav ? "img/star.png" : ""
        fillMode: Image.PreserveAspectCrop
    }

    Label {
        id: textLabel

        clip: true
        height: contentHeight
        anchors {
            top: nameLabel.bottom
            left: profileIcon.right
            leftMargin: nameLabel.anchors.leftMargin
            right: parent.right
            rightMargin: profileIcon.anchors.leftMargin
        }

        fontSize: "medium"
        wrapMode: Text.WordWrap
        elide: Text.ElideNone
        color: Theme.palette.normal.foregroundText
    }

    Label {
        id: timeLabel

        property date createdAt

        anchors {
            top: profileIcon.y + profileIcon.height > textLabel.y + textLabel.height
                 ? profileIcon.bottom
                 : textLabel.bottom
            left: profileIcon.right
            leftMargin: nameLabel.anchors.leftMargin
        }

        text: {
            // FIXME
            var now = new Date();
            if(now.getDate() - createdAt.getDate() > 0)
                return (now.getDate() - createdAt.getDate()) + i18n.tr(" days ago");
            if(now.getHours() - createdAt.getHours() > 0)
                return (now.getHours() - createdAt.getHours()) + i18n.tr(" hours ago");
            if(now.getMinutes() - createdAt.getMinutes() > 0)
                return (now.getMinutes() - createdAt.getMinutes()) + i18n.tr(" minutes ago");
            if(now.getSeconds() - createdAt.getSeconds() > 10)
                return (now.getSeconds() - createdAt.getSeconds()) + i18n.tr(" seconds ago");
            return i18n.tr("Just now");
        }

        fontSize: "small"
        elide: Text.ElideNone
        color: Theme.palette.normal.overlayText
    }

    Item {
        id: controlContainer
        property Item control
        // use the width of the control if there is (possibly elided) text,
        // or full width available if there is no text.
        anchors.fill: parent
        onControlChanged: {
            if (control) control.parent = controlContainer;
        }

        Connections {
            target: tweetItem.__mouseArea

            onClicked: {
//                console.debug(control)
                if (__mouseArea.mouseX > profileIcon.x
                        && __mouseArea.mouseX < profileIcon.x + profileIcon.width
                        && __mouseArea.mouseY > profileIcon.y
                        && __mouseArea.mouseY < profileIcon.y + profileIcon.height) {
                    profileIconClicked();
                } else {
                    tweetItem.clicked();
                }
            }

            onPressAndHold: {
//                if (control && control.enabled && __mouseArea.mouseX < progressionHelper.x && control.hasOwnProperty("pressAndHold")) {
                if (control && control.enabled && control.hasOwnProperty("pressAndHold")) {
                    control.pressAndHold();
                } else {
                    tweetItem.pressAndHold();
                }
            }
        }
    }

    onPressedChanged: {
        if (tweetItem.pressed && control && control.enabled) {
            tweetItem.__controlAreaPressed = true
        } else {
            tweetItem.__controlAreaPressed = false
        }
    }
}
