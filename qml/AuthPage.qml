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
import TwitterAPI 1.1
import "components"

Page {
    id: authPage
    title: qsTr("Twitter Authentication")

    Component.onCompleted: {
        state = "openAuthUrl"
        openAuthPageButton.enabled = false
        oauth.request_token()
    }

    Storage {
        id: storage
    }

    OAuth {
        id: oauth
        onStateChanged: {
            switch(state) {
            case OAuth.RequestTokenReceived:
                openAuthPageButton.enabled = true
                break
            case OAuth.UserAuthorizesRequestToken:
                authPage.state = "inputPin"
                break
            case OAuth.Authorized:
                storage.addAccount(screen_name, token, token_secret)
                stackView.push(timelineContainer)
                break
            }
        }
    }

    states: [
        State { name: "openAuthUrl"
            PropertyChanges { target: openAuthUrlCol; visible: true}
            PropertyChanges { target: inputPinCol; visible: false }
        },
        State { name: "inputPin"
            PropertyChanges { target: openAuthUrlCol; visible: false}
            PropertyChanges { target: inputPinCol; visible: true }
        }]

    ColumnLayout {
        id: openAuthUrlCol
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 25*dp
        }
        height: childrenRect.height
        spacing: 40*dp

        Label {
            id: authLabel

            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            text: qsTr("Welcome to Aztter\n\n" +
                       "You aren't logged in.\n" +
                       "Let's do twitter authentication.\n" +
                       "Please tap \"Open auth page\" button, and " +
                       "you will see Twitter authentication page.\n" +
                       "Please allow access from this app.")

            font.pointSize: 18
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }

        FlatButton {
            id: openAuthPageButton
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            fontPixelSize: 27*dp
            text: qsTr("Open auth page")
            onClicked: oauth.authorize()
        }
    }

    ColumnLayout {
        id: inputPinCol
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 25*dp
        }
        height: childrenRect.height
        spacing: 40*dp

        Label {
            id: inputPinLabel

            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            text: qsTr("Please input PIN.")

            font.pointSize: 18
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
        }

        TextField {
            id: pinInput

            Layout.fillWidth: true

            font.pixelSize: 28*dp
            placeholderText: qsTr("PIN")

            Keys.onReturnPressed: oauth.access_token(text)
        }

        FlatButton {
            id: accessTokenButton
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            fontPixelSize: 27*dp
            text: qsTr("Finish Authentication")
            onClicked: oauth.access_token(pinInput.text)
        }
    }
}
