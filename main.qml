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

MainView {
	id: mainView

    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "Aztter"

    // Note! applicationName needs to match the .desktop filename
    applicationName: "com.ubuntu.developer.yuntan.aztter"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    automaticOrientation: true

	width: units.gu(45)
	height: units.gu(80)

//    headerColor: "#00ba47" // DIC-598
//    backgroundColor: "#00c262" // DIC-92
//    footerColor: "#00a567" // DIC-173
    headerColor: "#5bdecd"
    backgroundColor: "#1EBBA6"
    footerColor: "#16ab97"

    Component.onCompleted: pageStack.push(loadingPage)

    Storage {
        id: storage
    }

	PageStack {
        id: pageStack

		Component {
			id: loadingPage
			LoadingPage {}
		}

        Component {
            id: pinAuthPage
            AuthPage {}
        }

		Component {
            id: timelineContainer
            TimelineContainer {}
		}
    }
}
