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
import "components"

Page {
	id: timelineContainer
	title: qsTr("Timeline")

//	onTitleIconClicked: openMenu()
	onTitleLabelClicked: timeline.positionTimelineAtBeginning()

	Timeline {
		id: timeline
		anchors.fill: parent
		z: 1
	}

	TweetBox {
		id: tweetBox

		z: 2
		visible: true
		anchors {
			left: parent.left
			right: parent.right
			bottom: parent.bottom
			margins: 5*dp
		}
	}

	Image {
		id: wallpaper

		z: 0
		anchors.fill: parent
		source: Qt.resolvedUrl("file:///C:/WorkSpace/wallpaper.jpg")
		fillMode: Image.PreserveAspectCrop
	}
}
