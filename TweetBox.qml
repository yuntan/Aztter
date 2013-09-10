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
    height: tweetEdit.height + units.gu(2)

    property string tmpText

    AztterStatusUpdate {
        id: aztter

        onStatusChanged: {
            animTimer.stop();
            switch(status) {
            case AztterStatusUpdate.Success:
                tweetEdit.text = i18n.tr("Tweet sent!");
                tmpText = "";
                break;
            default:
                tweetEdit.text = i18n.tr("Error occured!");
                break;
            }
            messageTimer.start();
        }
    }

    Timer {
        id: messageTimer

        interval: 3000
        onTriggered: {
            tweetEdit.text = tmpText;
            tweetEdit.enabled = true;
        }
    }

    Timer {
        id: animTimer

        property int i: 0
        interval: 500
        repeat: true
        triggeredOnStart: true

        onTriggered: {
            tweetEdit.text = i18n.tr("Sending") + ".";
            for(var j = 0; j < i%3; j++)
                tweetEdit.text += ".";
            i++;
        }
    }

    TextArea {
        id: tweetEdit

        Component.onCompleted: postButton.height = height

        anchors.margins: units.gu(1)
        anchors.left: parent.left
        anchors.right: postButton.left
        anchors.bottom: parent.bottom

        autoSize: true

        onTextChanged: {
            if(length >= 110){
                if(length >= 140){
                    // TODO: change color
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

        anchors.margins: units.gu(1)
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        text: i18n.tr("Post")
        onClicked: {
            tweetEdit.enabled = false;
            tmpText = tweetEdit.text;
            animTimer.start();
            aztter.tweet(tmpText);
        }
    }
}
