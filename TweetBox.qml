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

Item {
    height: tweetEdit.height

    AztterStatusUpdate {
        id: aztter

        onStatusChanged: {
            if(status === AztterStatusUpdate.Success)
                tweetEdit.text = "";
            postButton.enabled = true;
            tweetEdit.enabled = true;
        }
    }

    TextArea {
        id: tweetEdit

        Component.onCompleted: postButton.height = height

        anchors {
            margins: units.gu(1)
            left: parent.left
            right: postButton.left
            bottom: parent.bottom
        }

        autoSize: true

        onTextChanged: {
            postButton.enabled = true;
            if(length >= 110){
                if(length > 140){
                    postButton.enabled = false;
                } else if(length >= 130){
                    // TODO: change color
                }
                postButton.text = 140 - length
            } else {
                postButton.text = i18n.tr("Post")
            }
        }
    }

    Button {
        id: postButton

        enabled: false
        anchors {
            margins: units.gu(1)
            bottom: parent.bottom
            right: parent.right
        }

        text: i18n.tr("Post")
        onClicked: {
            if(tweetEdit.length != 0 && tweetEdit.length <= 140) {
                enabled = false;
                tweetEdit.enabled = false;
                aztter.tweet(tweetEdit.text);
            }
        }
    }
}
