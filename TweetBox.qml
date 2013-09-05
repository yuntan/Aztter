import QtQuick 2.0
import Ubuntu.Components 0.1
import "aztterplugin" 1.0

UbuntuShape {
    height: tweetEdit.height > postButton.height ? tweetEdit.height + units.gu(2)
                                                 : postButton.height + units.gu(2)

    color: Qt.rgba(174/255, 167/255, 159/255, 0.5)

    property string tmpText

    AztterStatusUpdate {
        id: aztter

        onStatusChanged: {
            animTimer.stop();
            switch(status) {
            case AztterStatusUpdate.Success:
                tweetEdit.text = i18n.tr("Tweet sent!");
                tmpText = "";
                break;
            default:
                tweetEdit.text = i18n.tr("Error occured!");
                break;
            }
            messageTimer.start();
        }
    }

    Timer {
        id: messageTimer

        interval: 3000
        onTriggered: {
            tweetEdit.text = tmpText;
            tweetEdit.enabled = true;
        }
    }

    Timer {
        id: animTimer

        property int i: 0
        interval: 500
        repeat: true
        triggeredOnStart: true

        onTriggered: {
            tweetEdit.text = i18n.tr("Sending") + ".";
            for(var j = 0; j < i%3; j++)
                tweetEdit.text += ".";
            i++;
        }
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
        onClicked: {
            tweetEdit.enabled = false;
            tmpText = tweetEdit.text;
            animTimer.start();
            aztter.tweet(tmpText);
        }
    }
}
