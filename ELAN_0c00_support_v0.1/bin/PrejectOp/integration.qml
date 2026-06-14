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
                text: "Press the button to integrate."
                font.pixelSize: 18
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                font.family: jbm.font
            }

            Button {
                text: "Integrate"
                font.family: jbm.font
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                onClicked: {
                    fileInt.copyFile(
                                    "PrejectOp/scripts/elan_auth",
                                    "/usr/local/bin/elan_auth"
                    )
                }
                Material.background: Material.Teal
                HoverHandler {
                        cursorShape: Qt.PointingHandCursor
                    }

            }
        }

        Connections {
            target: fileInt
            function onFilePlaced() { statusText.text = "Integrated Successfully!" }
            function onFileAlreadyThere() { statusText.text = "File already there." }
            function onScanError()    { statusText.text = "☹ Error. Possibly run as admin to solve this issue." }
        }
        Pane {
            width: 600
            anchors.bottomMargin: 5
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Material.background: Material.Red
            Material.elevation: 10
            TextEdit {
                text: "Write or paste the line 'auth    [success=done default=ignore] pam_exec.so quiet /usr/local/bin/elan_auth' in /etc/pam.d/gdm-password using 'nano /etc/pam.d/gdm-password' to use the integrated file in your gdm login manager. You can also paste this into /etc/pam.d/sudo to use fingerprint sensor in the terminal. ThankYou!"


                cursorVisible: true
                selectByMouse: true
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                color: "#fefefe"
            }
        }


}
