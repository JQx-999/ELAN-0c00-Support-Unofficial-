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
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        onClicked: stackView.pop()
        HoverHandler {
                cursorShape: Qt.PointingHandCursor
            }
        font.family: jbm.font
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
                text: "Press the button to remove fingerprint."
                font.pixelSize: 18
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                font.family: jbm.font
            }

            Button {
                text: "Remove"
                font.family: jbm.font
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                onClicked: removeBridge.startRemove()
                Material.background: Material.Amber
                HoverHandler {
                        cursorShape: Qt.PointingHandCursor
                    }

            }
        }

        Connections {
            target: removeBridge
            function onRemoveStarted() { statusText.text = "Removing Now..." }
            function onFingerprintRemoved() { statusText.text = "✓ Success!" }
            function onScanError()    { statusText.text = "☹ Error. Possibly run as admin to solve this issue." }
        }
}
