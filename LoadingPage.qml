import QtQuick 2.0
import Ubuntu.Components 0.1

Page {
    id: loadingPage

    title: i18n.tr("Aztter")

    UbuntuShape {
        width: 200
        height: width
        anchors.centerIn: parent
        color : UbuntuColors.orange

        Label {
            id: loadingLabel
            objectName: "loadingLabel"
            anchors.centerIn: parent

            text: i18n.tr("Loading...")
        }
    }
}
