import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import TwitterAPI 1.1
import "components"

Item {
    id: box

    height: mainRow.height + 10*dp

    Status {
        id: tweet

        onLoadingChanged: {
            if(loading === false) {
                postButton.enabled = false
                tweetEdit.enabled = true
                if(postStatus === Status.Success) {
                    updateStatusBar(qsTr("Tweet sent."))
                    tweetEdit.text = ""
                } else {
                    switch(postStatus) {
                    case Status.RateLimitExceeded:
                        updateStatusBar(qsTr("Rete limit exceeded."))
                        break
                    case Status.OverCapacity:
                        updateStatusBar(qsTr("Twitter is now over capacity."))
                        break
                    case Status.InternalError:
                        updateStatusBar(qsTr("Internal error occurd in twitter."))
                        break
                    case Status.TimeInvalid:
                        updateStatusBar(qsTr("Your computer's time is not valid. Please fix it."))
                        break
                    case Status.Duplicate:
                        updateStatusBar(qsTr("Tweet duplicated."))
                        break
                    default:
                        updateStatusBar(qsTr("Unknown error."))
                    }
                }
            }
        }
    }

    function postTweet() {
        postButton.enabled = false;
        tweetEdit.enabled = false;
        tweet.statusesUpdate({"status": tweetEdit.text})
    }

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "#c00585d1"
        radius: height / 3
    }

    RowLayout {
        id: mainRow

        height: tweetEdit.height
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 5*dp
        }
        spacing: 5*dp

        TextField {
            id: tweetEdit

            Layout.fillWidth: true

            font.pixelSize: 24*dp
            placeholderText: qsTr("What's happened?")

            Keys.onReturnPressed: {
                if(event.modifiers & Qt.ControlModifier || event.modifiers & Qt.ShiftModifier)
                    postTweet();
                else
                    event.accepted = false;
            }

            onTextChanged: {
                postButton.enabled = true;
                postButton.text = qsTr("Post")
                if(length >= 110){
                    if(length > 140){
                        postButton.enabled = false;
                    } else if(length >= 130){
                        // TODO: change color
                    }
                    postButton.text = 140 - length
                } else if(length == 0){
                    postButton.enabled = false;
                }
            }
        }

        FlatButton {
            id: postButton

            Layout.preferredWidth: implicitWidth
            Layout.fillHeight: true

            enabled: false
            text: qsTr("Post")
            onClicked: postTweet()
        }
    }

//	FastBlur {
//		anchors.fill: rect
//		source: parent.parent
//		radius: 64
//	}
}
