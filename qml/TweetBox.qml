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
import "components"
import "aztterplugin" 1.0

Rectangle {
    function postTweet() {
        postButton.enabled = false;
        tweetEdit.enabled = false;
        aztter.tweet(tweetEdit.text);
    }

    color: "#035102"

    AztterStatusUpdate {
        id: aztter

        onStatusChanged: {
            if(status === AztterStatusUpdate.Success)
                tweetEdit.text = "";
            postButton.enabled = true;
            tweetEdit.enabled = true;
        }
    }

    FlatButton {
        id: openButton

        width: height
        height: parent.height
        anchors {
            left: parent.left
        }

        iconSource: "img/star.png"

//        onClicked: stackView.push()
    }

    TextField {
        id: tweetEdit

        anchors {
            top: parent.top
            topMargin: parent.height / 5
            bottom: parent.bottom
            bottomMargin: parent.height / 5
            left: openButton.right
            right: postButton.left
        }

        font.pixelSize: height / 2
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

        height: parent.height
        width: height * 3 / 2
        anchors.right: parent.right

        enabled: false
        text: qsTr("Post")
        textColor: "white"
        onClicked: postTweet()
    }
}
