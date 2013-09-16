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
import QtQuick.LocalStorage 2.0 as Storage
import QtWebKit 3.0
import Ubuntu.Components 0.1
import "aztterplugin" 1.0

Page {
	id: pinAuthPage

	title: i18n.tr("Authentication")

    AztterOAuth {
        id: aztterOAuth

        onAuthPageRequested: authWebView.url = authPageUrl
        onAuthorized: {
            aztterOAuth.destroy()
            pageStack.push(timelineContainer)
        }
    }

	ActivityIndicator {
		anchors.centerIn: parent
		running: authWebView.loading
	}

	Rectangle {
		id: authLabel
		width: parent.width

		Label {
			anchors.centerIn: parent
			text: i18n.tr("Let's do twitter authentication first.")
			fontSize: "large"
		}
	}

	WebView {
		id: authWebView
		width: parent.width
        height: parent.height - authLabel.height - units.gu(3)
        anchors.bottom: parent.bottom
	}
}
