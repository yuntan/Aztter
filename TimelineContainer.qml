import QtQuick 2.0
import Ubuntu.Components 0.1

Page {
    id: timelineContainer

    Component.onCompleted: {
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
        currentIndex = index;
    }

//    AztterSettings {
//        id: settings
//    }

    Tabs {
        id: tabs

        onSelectedTabIndexChanged: loadListView(selectedTabIndex)
        Tab {title: i18n.tr("Home")}
        Tab {title: i18n.tr("Mention")}
        Tab {title: i18n.tr("List")}
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
        flickableItem: listView
    }

        z: 0
    }
}
