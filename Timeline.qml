import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import "aztterplugin" 1.0

ListView {
    id: homeTLView

    function loadStart() {
        helper.startFetching();
    }
    function loadStop() {
        helper.streamDisconnect();
    }

    clip: true
    Component.onCompleted: helper.startFetching()

    AztterHomeTLHelper {
        id: helper
        onTweetReceived: listModel.prepend(tweet)
        onTweetDeleted: listModel.remove(tweetId)
        onFavChanged: listModel.changeFav(tweetId, fav)
    }

    AztterTweetListModel {
        id: listModel
    }

    model: listModel
    delegate: TweetItem {
        text: tweetText
        name: userName
        screenName: "@" + userScreenName
        iconSource: userProfileImageUrl

        onItemSwipedLeft: helper.fav(tweetId)
        onItemSwipedRight: helper.rt(tweetText, userScreenName)
    }
}
