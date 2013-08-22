import QtQuick 2.0
import QtWebKit 3.0
import Ubuntu.Components 0.1

Page {
	id: pinAuthPage

	title: i18n.tr("Authentication")

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

	Label {
		id: pinText
		anchors.left: parent.left
		anchors.bottom: authWebView.top
		fontSize: "x-large"
		text: "PIN : "
	}

	TextField {
		id: pinTextField
		width: parent.width - pinText.width
		anchors.right: parent.right
		anchors.bottom: authWebView.top
	}

	WebView {
		id: authWebView
		width: parent.width
		height: parent.height - authLabel.height - pinTextField.height - units.gu(3)
		anchors.bottom: parent.bottom
		url: "http://mobile.twitter.com"
	}
}
