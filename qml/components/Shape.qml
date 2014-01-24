import QtQuick 2.2

Rectangle {

    property var image: internalImage.data

    Rectangle {
        id: intrRect
        clip: true
        anchors.fill: parent
    }


}
