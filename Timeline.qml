import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import "aztterplugin" 1.0

ListView {
    clip: true

    Component.onCompleted: helper.startFetching()

    model: listModel
    delegate: TweetItem {
        text: tweetText
        name: userName
        screenName: "@" + userScreenName
        iconSource: userProfileImageUrl
    }

    AztterHomeTLHelper {
        id: helper
        onTweetReceived: listModel.prepend(tweet)
    }

    AztterTweetListModel {
        id: listModel
    }

    Scrollbar {
        flickableItem: parent
    }
}
