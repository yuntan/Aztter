import QtQuick 2.1
import QtQuick.Controls 1.0
import QtGraphicalEffects 1.0

Rectangle {
    // ensure children added do not draw over the titleBar
    property alias data: main.data
    property alias title: titleLabel.text
    property color mainColor: "#1EBBA6"
    property color titleColor: "green"
    property alias busy: busyIndicator.running

    color: mainColor

    // use container in order not titleBarShadow to be clipped
    // see http://stackoverflow.com/questions/15488714/how-to-create-drop-shadow-for-rectangle-on-qtquick-2-0
    Item {
        id: titleBarContainer

        z: 10
        visible: false
        width: parent.width
        height: parent.height / 10

        Rectangle {
            id: titleBar

            anchors.top: parent.top
            width: parent.width
            height: parent.height - titleBarShadow.radius

            color: titleColor

            Label {
                id: titleLabel

                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: parent.width / 20
                }

                color: "white"
                font.pixelSize: parent.height / 2
                fontSizeMode: Text.HorizontalFit
                font.bold: true
                style: Text.Raised
            }

            BusyIndicator {
                id: busyIndicator

                width: height
                anchors {
                    top: parent.top
                    margins: parent.height / 6
                    bottom: parent.bottom
                    right:parent.right
                }
            }
        }
    }

    DropShadow {
        id: titleBarShadow

        z: 10
        anchors.fill: source

        horizontalOffset: 0
        verticalOffset: titleBarContainer.height / 10
        radius: verticalOffset
        samples: radius * 2
        color: "#80000000"
        source: titleBarContainer
    }

    Item {
        id: main

        z:5
        anchors {
            top: titleBarContainer.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }
}
