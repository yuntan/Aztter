import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Button {
	style: ButtonStyle {
		background: Rectangle {
			width: control.width; height: control.height
			color: control.pressed ? "#80000000" : "transparent"
			Rectangle {
				id: rect
				anchors.fill: parent
				anchors.margins: 2
				color: "transparent"
				border.color: "white"
				border.width: 2
			}
		}

		label: Label {
			anchors.fill: control
			anchors.margins: 3
			color: "whitesmoke"
			text: control.text
			font.pixelSize: control.height - 6
			font.bold: true
			maximumLineCount: 1
			horizontalAlignment: Text.AlignHCenter
		}
	}
}
