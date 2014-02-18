import QtQuick 2.2
import QtQuick.Controls 1.1
import TwitterAPI 1.1

Rectangle {
    id: loadingPage

    Component.onCompleted: timer.start()

    color: "#1fc4ab"

    OAuth {
        id: oauth
    }

    Timer {
        id: timer

        interval: 1000
        onTriggered: {
            if(storage.isAuthenticated()) {
                oauth.token = storage.oauthToken(0)
                oauth.token_secret = storage.oauthTokenSecret(0)
                stackView.push(timelineContainer)
            } else { stackView.push(authPage) }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 40*dp

        Label {
            id: loadingLabel

            anchors.horizontalCenter: parent.horizontalCenter
            color: Qt.darker(loadingPage.color, 0.5)
            text: qsTr("Loading...")
            font.pointSize: 24
        }

        BusyIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            running: true
        }
    }
}
