import QtQuick 2.0
import Ubuntu.Components 0.1

MainView {
	id: mainView

    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the .desktop filename
    applicationName: "Aztter"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    automaticOrientation: true

	width: units.gu(45)
	height: units.gu(80)

	PageStack {
		id: pageStack

//		Component.onCompleted: push(loadingPage)
		Component.onCompleted: push(pinAuthPage)

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
