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
import QtWebKit 3.0
import "components"
import "aztterplugin" 1.0

Page {
    id: authPage

    title: qsTr("Twitter Authentication")
    busy: authWebView.loading

    AztterAuthHelper {
        id: aztterOAuth

        onAuthPageRequested: authWebView.url = authPageUrl
        onAuthorized: stackView.push(timelineContainer)
    }

        Label {
            id: authLabel

            width: parent.width
            anchors.top: parent.top
            text: qsTr("Let's do twitter authentication first.")
            font.pointSize: 18
            color: "white"
        }


    WebView {
        id: authWebView
        width: parent.width
        anchors.top: authLabel.bottom
        anchors.topMargin: parent.height / 20
        anchors.bottom: parent.bottom
    }
}
