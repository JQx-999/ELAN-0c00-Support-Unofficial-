import QtQuick 2.15
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
        font.family: jbm.font
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
                text: "Press the button to remove integration."
                font.pixelSize: 18
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }

            Button {
                text: "Remove Integration"
                font.family: jbm.font
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                onClicked: removalHeHe.removeFile("/usr/local/bin/elan_auth")
                Material.background: Material.Indigo
                HoverHandler {
                        cursorShape: Qt.PointingHandCursor
                    }

            }
        }

        Connections {
            target: removalHeHe
            function onFileNotExist() { statusText.text = "No integration found!" }
            function onFileRemoved() { statusText.text = "Removed Integration successfully!" }
            function onScanError()    { statusText.text = "☹ Error. Possibly run as admin to solve this issue." }
        }
}
