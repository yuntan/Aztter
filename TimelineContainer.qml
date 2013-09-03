import QtQuick 2.0
import Ubuntu.Components 0.1

Page {

    title: "Aztter"
    Component.onCompleted: {
        tweetBox.z = 10
    }

    Timeline {
        id: homeTimeline

        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height
        z: 5
    }

    TweetBox {
        id: tweetBox

        anchors.bottom: parent.bottom
        anchors.bottomMargin: units.gu(1)
        width: parent.width
        z: 0
    }
}
