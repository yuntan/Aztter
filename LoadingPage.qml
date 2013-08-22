import QtQuick 2.0
import Ubuntu.Components 0.1

Page {
    id: loadingPage

    title: i18n.tr("Aztter")

	ActivityIndicator {
		anchors.right: parent.right
		running: true //TODO: check
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
			color: UbuntuColors.white

            text: i18n.tr("Loading...")
        }
    }
}
