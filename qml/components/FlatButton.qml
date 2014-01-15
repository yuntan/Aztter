import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Button {
	property int fontPixelSize: 0

	style: ButtonStyle {
		background: Rectangle {
			width: control.width; height: control.height
			color: control.pressed ? "#80000000" : "transparent"
			Rectangle {
				anchors.fill: parent
				anchors.margins: 2*dp
				color: "transparent"
				border.color: "white"
				border.width: 2*dp
			}
		}

		label: Label {
			id: innerLabel
			color: "whitesmoke"
			text: control.text
			font.bold: true
			font.pixelSize: 21*dp
			maximumLineCount: 1
			horizontalAlignment: Text.AlignHCenter

			Component.onCompleted: {
				control.fontPixelSize !== 0
						? font.pixelSize = control.fontPixelSize
						: control.fontPixelSize = font.pixelSize
				control.implicitWidth = implicitWidth + 24*dp
				control.implicitHeight = implicitHeight + 12*dp
			}

			Connections	{
				target: control
				onFontChanged: font = control.font
				onFontPixelSizeChanged: font.pixelSize = control.fontPixelSize
			}
		}
	}
}
