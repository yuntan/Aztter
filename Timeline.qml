import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import "aztterplugin" 1.0

Item {
    clip: true

    Component.onCompleted: aztterUserStream.startFetching()

    function createTweetItem(name, screenName, text) {
        var component = Qt.createComponent("TweetItem.qml");
        var item = component.createObject(column, {
                                              name: name,
                                              screenName: screenName,
                                              text: text
                                          });

        if (item == null) {
            // Error Handling
            console.log("Error creating TweetItem");
        }
    }

    AztterHomeTLHelper {
        id: aztterUserStream

        onTweetReceived: createTweetItem(name, screenName, text)
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height
        interactive: contentHeight > height

        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }

    Scrollbar {
        flickableItem: flickable
    }
}
