import QtQuick 2.0
import Ubuntu.Components 0.1

/*!
    \brief MainView with a Label and Button elements.
*/

MainView {
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the .desktop filename
    applicationName: "Aztter"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    automaticOrientation: true

    width: units.gu(40)
    height: units.gu(75)

    signal buttonClicked()

    function updateText(t) {label.text = t}

    Page {
        title: i18n.tr("Simple")

        Column {
            spacing: units.gu(1)
            anchors {
                margins: units.gu(2)
                fill: parent
            }

            UbuntuShape {
                width: 200
                height: width

                Label {
                    id: label
                    objectName: "label"
                    anchors.centerIn: parent

                    text: i18n.tr("Hello...")
                }
            }

            Button {
                objectName: "button"
                width: parent.width

                text: i18n.tr("Tap me!")
                onClicked: {
                    buttonClicked()
                }
            }
        }
    }
}
