import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Item {
    Rectangle {
            width: parent.width
            height: parent.height
            color: "#292929"
    }
    FontLoader {
            id: jbm
            source: "fonts/JetBrainsMono-VariableFont_wght.ttf"
        }
    Button {
        text: "🢨 Back"
        font.family: jbm.font
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        onClicked: stackView.pop()
        HoverHandler {
                cursorShape: Qt.PointingHandCursor
            }
    }
    Rectangle {
            width: 600
            height: 200
            color: "#80FF0000"

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            ColorAnimation on color { to: "#4d2600"; duration: 500 }
            radius: 20

            Text {
                id: statusText
                font.family: jbm.font
                text: "Press the button to scan."
                font.pixelSize: 18
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }

            Button {
                text: "Scan Fingerprint"
                font.family: jbm.font
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                onClicked: enrollBridge.startScan()
                Material.background: Material.Pink
                HoverHandler {
                        cursorShape: Qt.PointingHandCursor
                    }

            }
        }

        Connections {
            target: enrollBridge
            function onEnrollStarted() { statusText.text = "♦ Touch the sensor..." }
            function onFingerprintAdded() { statusText.text = "✓ Successfully Added!" }
            function onExistingFinger()  { statusText.text = "✗ Fingerprint is already added!" }
            function onScanError()    { statusText.text = "☹ Error. Possibly run as admin to solve this issue." }
        }
}
