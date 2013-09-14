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

Page {
    id: timelineContainer

    Component.onCompleted: {
        if(wallpaper.status === Image.Ready)
            filter.color = Qt.rgba(56/255, 56/255, 55/255, 0.5) // DIC-G300
        tweetBox.visible = true;
//        loadListView(settings.load("view/last_view"));
        loadListView(0)
    }

    property int currentIndex: -1
    property QtObject listView
    function loadListView(index) {
        console.debug("loadListView(" + index + ")");
        if(currentIndex != -1){
            listView.loadStop();
            listView.destroy();
        }
        var component = Qt.createComponent("Timeline.qml");
        listView = component.createObject(timelineContainer,
                                          {"anchors.fill": timelineContainer, "z": 12});
        flickable = listView;
        scrollBar.flickableItem = listView;
        currentIndex = index;
    }

    Tabs {
        id: tabs

        onSelectedTabIndexChanged: loadListView(selectedTabIndex)
        Tab {title: i18n.tr("Home")}
//        Tab {title: i18n.tr("Mention")}
//        Tab {title: i18n.tr("List")}
    }

    TweetBox {
        id: tweetBox

        z: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: units.gu(2)
        width: parent.width
    }

    Scrollbar {
        id: scrollBar

        z: 20
    }

//    Component {
//        id: wallpaperComponent

        Image {
            id: wallpaper

            z: 0
            anchors.fill: parent
            source: "wallpaper"
            fillMode: Image.PreserveAspectCrop
        }

        Rectangle {
            id: filter

            z: 1
            anchors.fill: parent
            color: Qt.rgba(56/255, 56/255, 55/255, 0.3) // DIC-G300
        }
//    }
}
