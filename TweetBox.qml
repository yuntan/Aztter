import QtQuick 2.0
import Ubuntu.Components 0.1
import "aztterplugin" 1.0

UbuntuShape {
    height: tweetEdit.height > postButton.height ? tweetEdit.height + units.gu(2)
                                                 : postButton.height + units.gu(2)

    color: "transparent"

    AztterStatusUpdate {
        id: aztter
    }

    TextArea {
        id: tweetEdit

        anchors.margins: units.gu(1)
        anchors.left: parent.left
        anchors.right: postButton.left
        anchors.bottom: parent.bottom

        autoSize: true
    }

    Button {
        id: postButton

        anchors.margins: units.gu(1)
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        text: i18n.tr("Post")
        onClicked: aztter.tweet = tweetEdit.text
    }
}
