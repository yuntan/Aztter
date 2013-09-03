import QtQuick 2.0
import Ubuntu.Components 0.1
import "aztterplugin" 1.0

Page {
    id: loadingPage

    title: i18n.tr("Aztter")

    Component.onCompleted: timer.start()

    AztterLoadingPageHelper {
        id: helper

        onLoadingTextChanged: loadingLabel.text = loadingText
    }

    Timer {
        id: timer

        interval: 3000
        onTriggered: {
            if(helper.isAuthenticated){
                parent.destroy()
                pageStack.push(timelineContainer)
            } else {
                pageStack.push(pinAuthPage)
            }
        }
    }

	ActivityIndicator {
		anchors.right: parent.right
//		running: true
	}

    UbuntuShape {
        width: 200
        height: width
        anchors.centerIn: parent
        color : UbuntuColors.orange

        Label {
            id: loadingLabel
            objectName: "loadingLabel"
            anchors.centerIn: parent
            color: "white"

            text: i18n.tr("Loading...")
        }
    }
}
