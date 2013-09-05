import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import "aztterplugin" 1.0

ListItem.Empty {
    id: tweetItem

    property alias text: textLabel.text
    property alias name: nameLabel.text
    property alias iconSource: iconImage.source
    property alias screenName: screenNameLabel.text

    property alias control: controlContainer.control
    __acceptEvents: false
    property bool __controlAreaPressed: false

    width: parent.width
    height: Math.max(profileIcon.height + profileIcon.anchors.topMargin * 2,
                     nameLabel.anchors.topMargin + nameLabel.height + textLabel.height + textLabel.anchors.bottomMargin)

    Rectangle {
        id: controlHighlight

        visible: tweetItem.swipingState === "" ? control && __controlAreaPressed : false
        anchors.fill: parent
        color: Theme.palette.selected.base
    }

    UbuntuShape {
        id: profileIcon

        width: height
        height: units.gu(7)
        anchors {
            top: parent.top
            topMargin: units.gu(1)
            left: parent.left
            leftMargin: units.gu(1)
        }

        radius: "medium"
        image: Image {
            id: iconImage

            fillMode: Image.PreserveAspectCrop

            property url fallbackSource: Qt.resolvedUrl("Aztter80.png")

            Component.onCompleted: {
                if(source == undefined || source == "")
                    source = fallbackSource
            }
        }
    }

    Label {
        id: nameLabel

        clip: true
        anchors {
            top: parent.top
            topMargin: profileIcon.anchors.topMargin
            left: profileIcon.right
            leftMargin: units.gu(1)
        }

        maximumLineCount: 1
        elide: Text.ElideRight
        color: Theme.palette.normal.baseText
        font.bold: true
    }

    Label {
        id: screenNameLabel

        clip: true
        width: parent.width - (profileIcon.anchors.leftMargin + profileIcon.width +
                               nameLabel.anchors.leftMargin + nameLabel.width +
                               screenNameLabel.anchors.leftMargin * 2 +
                               timeLabel.width + timeLabel.anchors.rightMargin)
               > 0 ?
               parent.width - (profileIcon.anchors.leftMargin + profileIcon.width +
                               nameLabel.anchors.leftMargin + nameLabel.width +
                               screenNameLabel.anchors.leftMargin * 2 +
                               timeLabel.width + timeLabel.anchors.rightMargin)
               : 0
        anchors {
            left: nameLabel.right
            leftMargin: units.gu(1)
            bottom: nameLabel.bottom
        }

        fontSize: "small"
        maximumLineCount: 1
        elide: Text.ElideRight
        color: Theme.palette.normal.overlayText
    }

    Label {
        id: timeLabel

        anchors {
            bottom: nameLabel.bottom
            right: parent.right
            rightMargin: profileIcon.anchors.leftMargin
        }

        text: "time"
        fontSize: "small"
        elide: Text.ElideNone
        color: Theme.palette.normal.overlayText

    }

    Label {
        id: textLabel

        height: contentHeight
        anchors {
            top: nameLabel.bottom
            bottomMargin: units.gu(1)
            left: profileIcon.right
            leftMargin: nameLabel.anchors.leftMargin
            right: parent.right
            rightMargin: profileIcon.anchors.leftMargin
        }
        clip: true

        fontSize: "medium"
        wrapMode: Text.WordWrap
        elide: Text.ElideNone
        color: Theme.palette.normal.foregroundText
    }

    Item {
        id: controlContainer
        property Item control
        // use the width of the control if there is (possibly elided) text,
        // or full width available if there is no text.
//        width: control ? control.width : undefined
//        height: control ? control.height : undefined
//        anchors {
//            right: parent.right
////            rightMargin: tweetItem.__contentsMargins
//            verticalCenter: parent.verticalCenter
//        }
        anchors.fill: parent
        onControlChanged: {
            if (control) control.parent = controlContainer;
        }

        Connections {
            target: tweetItem.__mouseArea

            onClicked: {
//                if (control && __mouseArea.mouseX < progressionHelper.x) {
                if (control) {
                    if (control.enabled && control.hasOwnProperty("clicked"))
                        control.clicked();
                } else {
                    tweetItem.clicked();
                }
            }

            onPressAndHold: {
//                if (control && control.enabled && __mouseArea.mouseX < progressionHelper.x && control.hasOwnProperty("pressAndHold")) {
                if (control && control.enabled && control.hasOwnProperty("pressAndHold")) {
                    control.pressAndHold();
                } else {
                    tweetItem.pressAndHold();
                }
            }
        }
    }

    onPressedChanged: {
        if (tweetItem.pressed && control && control.enabled && (__mouseArea.mouseX < progressionHelper.x)) {
            tweetItem.__controlAreaPressed = true
        } else {
            tweetItem.__controlAreaPressed = false
        }
    }
}
