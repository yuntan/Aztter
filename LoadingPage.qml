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

Page {
    id: loadingPage

    title: i18n.tr("Aztter")

    Component.onCompleted: timer.start()

    AztterLoadingPageHelper {
        id: helper

        onLoadingTextChanged: loadingLabel.text = loadingText
    }

    Timer {
        id: timer

        interval: 3000
        onTriggered: {
            if(helper.isAuthenticated){
                parent.destroy()
                pageStack.push(timelineContainer)
            } else {
                pageStack.push(pinAuthPage)
            }
        }
    }

	ActivityIndicator {
		anchors.right: parent.right
//		running: true
	}

    UbuntuShape {
        width: 200
        height: width
        anchors.centerIn: parent
        color : UbuntuColors.orange

        Label {
            id: loadingLabel
            objectName: "loadingLabel"
            anchors.centerIn: parent
            color: "white"

            text: i18n.tr("Loading...")
        }
    }
}
