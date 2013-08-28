import QtQuick 2.0
import QtWebKit 3.0
import Ubuntu.Components 0.1
import "aztterplugin" 1.0

Page {
	id: pinAuthPage

	title: i18n.tr("Authentication")

    AztterOAuth {
        id: aztterOAuth

        onOauthUrlChanged: authWebView.url = oauthUrl
        onAuthorized: pageStack.push(timelineContainer)
    }

	ActivityIndicator {
		anchors.centerIn: parent
		running: authWebView.loading
	}

	Rectangle {
		id: authLabel
		width: parent.width

		Label {
			anchors.centerIn: parent
			text: i18n.tr("Let's do twitter authentication first.")
			fontSize: "large"
		}
	}

	WebView {
		id: authWebView
		width: parent.width
        height: parent.height - authLabel.height - units.gu(3)
        anchors.bottom: parent.bottom
	}
}
