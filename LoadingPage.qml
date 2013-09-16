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

    Timer {
        id: timer

        interval: 2000
        onTriggered: {
            if(storage.isAuthenticated())
                pageStack.push(timelineContainer);
            else
                pageStack.push(pinAuthPage);
            loadingPage.destroy()
        }
    }

	ActivityIndicator {
		anchors.right: parent.right
//		running: true
	}

    Label {
        id: loadingLabel

        anchors.centerIn: parent
        color: "white"
        fontSize: "large"
        text: i18n.tr("Loading...")
    }
}
