import QtQuick 2.0
import Ubuntu.Components 0.1

MainView {
	id: mainView

    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "Aztter"

    // Note! applicationName needs to match the .desktop filename
    applicationName: "Aztter"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    automaticOrientation: true

	width: units.gu(45)
	height: units.gu(80)

    headerColor: "#00ba47" // DIC-598
    backgroundColor: "#00c262" // DIC-92
    footerColor: "#00a567" // DIC-173

	PageStack {
		id: pageStack

        Component.onCompleted: push(loadingPage)

		Component {
			id: loadingPage
			LoadingPage {}
		}

        Component {
            id: pinAuthPage
            PinAuthPage {}
        }

		Component {
            id: timelineContainer
            TimelineContainer {}
		}
    }
}
