import QtQuick 2.0
import Ubuntu.Components 0.1

Page {
    id: root

    title: i18n.tr("Authentication")

    Rectangle {
        color: UbuntuColors.coolGrey

        Label {
            anchors.centerIn: parent
            text: i18n.tr("Let's do twitter authentication first.")
            fontSize: large
        }
    }
}
