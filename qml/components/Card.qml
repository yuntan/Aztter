import QtQuick 2.2

Item {
	id: _card

	property alias data: main.data

	signal clicked()

	Rectangle {
		id: main

		anchors {
			top: parent.top
			bottom: bottomShadow.top
			left: parent.left
			right: rightShadow.left
		}

		color: "#80ffffff"

		MouseArea {
			onClicked: _card.clicked()
			onPressedChanged: {
				if(pressed) { main.color = Qt.darker("#80ffffff", 1.2) }
				else { main.color = "#c0ffffff" }
			}
		}
	}

	// right shadow
	Rectangle {
		id: rightShadow
		anchors.right: parent.right
		width: 0.5*mm; height: parent.height
		color: "#80000000"
	}

	//bottom shadow
	Rectangle {
		id: bottomShadow
		anchors.bottom: parent.bottom
		width: parent.width; height: 0.5*mm
		color: "#80000000"
	}
}
