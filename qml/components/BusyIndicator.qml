import QtQuick 2.1

Item {
    id: indicator

    property bool running: false
    property int delay: 0

    onRunningChanged: {
        if(!running) opacity = 0
    }

    opacity: 0
    Behavior on opacity {PropertyAnimation { duration: 250 }}

    Timer {
        interval: parent.delay
        running: parent.running
        repeat: false
        onTriggered: opacity = 1
    }

    Image {
        id: rotatorImg

        anchors.fill: parent
        source: "../../img/rotation_icon.png"

        NumberAnimation on rotation {
            running: indicator.running
            from: 0; to: 360
            loops: NumberAnimation.Infinite
            duration: 1000
        }
    }
}
