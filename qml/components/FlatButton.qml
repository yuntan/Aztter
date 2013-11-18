import QtQuick 2.0

Item {
    property alias iconSource: icon.source
    property alias text: label.text
    property alias textColor: label.color
//    property Menu menu //TODO

    signal clicked()

    Component.onCompleted: {
        if(iconSource === "" || iconSource == undefined)
            icon.visible = false
        else
            icon.visible = true
        if(text === "" || text == undefined)
            label.visible = false
        else
            label.visible = true
    }

    Image {
        id: icon

        width: height
        height: parent.height / 2
        anchors.centerIn: parent
    }

    Text {
        id: label

        anchors.centerIn: parent
        font.pixelSize: parent.height / 2
    }

    Rectangle {
        id: filter

        anchors.fill: parent
        visible: false
        color: "#80000000"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: parent.clicked()
        onPressedChanged: {
            if(pressed) filter.visible = true
            else filter.visible = false
        }
    }
}
