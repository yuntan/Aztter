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

Rectangle {
    id: loadingPage

    Component.onCompleted: timer.start()

    color: "#1fc4ab"

    Timer {
        id: timer

        interval: 2000
        onTriggered: {
            if(storage.isAuthenticated())
                stackView.push(timelineContainer);
            else
                stackView.push(authPage);
        }
    }

//	ActivityIndicator {
//		anchors.right: parent.right
////		running: true
//	}

    Label {
        id: loadingLabel

        anchors.centerIn: parent
        color: Qt.darker(parent.color, 0.5)
        text: qsTr("Loading...")
        font.pointSize: 18
    }
}
