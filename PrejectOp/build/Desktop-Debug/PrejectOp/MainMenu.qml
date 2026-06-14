import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Effects
import QtMultimedia 6.5

Item {
    FontLoader {
            id: jbm
            source: "fonts/JetBrainsMono-VariableFont_wght.ttf"
        }
    MediaPlayer {
            id: player
            source: "Images/back.mp4"

            loops: MediaPlayer.Infinite
            audioOutput: undefined
            videoOutput: videoOutput

            Component.onCompleted: {
                player.play()
            }
        }
    VideoOutput {
            id: videoOutput
            anchors.fill: parent
            fillMode: VideoOutput.PreserveAspectCrop
        }

    Image {
        source: "Images/icon.png"
        width: 500
        height: 500
        opacity: 0.5
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 300
        anchors.topMargin: 100
    }
    Image {
        source: "Images/title.png"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Material.elevation: 20
        opacity: 1
    }


    Rectangle {
        id: rectnigga
        radius: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width: 575
        height: 320
        anchors.bottomMargin: 55
        opacity: 0.1
        border.color: "#ffffff"


    }


    Column {
        anchors.bottom: parent.bottom
        anchors.left : parent.left
        anchors.leftMargin: 65
        anchors.bottomMargin: 75
        spacing: 5
        opacity: 0.9



        Button {
            text: "Test Fingerprint"
            id: button1
            width: 250
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: stackView.push("TestPage.qml")
            Material.background: Material.Green
            Material.elevation: 6
            font.family: jbm.font
            HoverHandler {
                    cursorShape: Qt.PointingHandCursor
                }

        }
        Button {
            text: "Enroll Finger"
            width: 250
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: stackView.push("EnrollPage.qml")
            font.family: jbm.font
            Material.background: Material.Pink
            HoverHandler {
                    cursorShape: Qt.PointingHandCursor
                }
        }
        Button {
            text: "Delete Finger"
            width: 250
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: stackView.push("DeletePage.qml")
            font.family: jbm.font
            Material.background: Material.Amber
            HoverHandler {
                    cursorShape: Qt.PointingHandCursor
                }
        }
        Button {
            text: "Integrate with GDM"
            width: 250
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: stackView.push("integration.qml")
            font.family: jbm.font
            HoverHandler {
                    cursorShape: Qt.PointingHandCursor
                }
            Material.background: Material.Teal
        }
        Button {
            text: "Remove GDM Integration"
            width: 250
            anchors.horizontalCenter: parent.horizontalCenter

            font.family: jbm.font
            onClicked: stackView.push("removal.qml")
            Material.background: Material.Indigo
            Material.foreground: "#000000"
            opacity: 1
            HoverHandler {
                    cursorShape: Qt.PointingHandCursor
                }

        }
    }
    Button {
        text: "Exit"

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.bottomMargin: 215
        width: 100
        onClicked: Qt.quit()
        font.family: jbm.font

        Material.background: Material.Red

        opacity: 1
        HoverHandler {
                cursorShape: Qt.PointingHandCursor
            }

    }
    Button {
        text: "About"
        width: 100
        Material.background: Material.BlueGrey
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 100
        anchors.bottomMargin: 165
        onClicked: stackView.push("about.qml")
        HoverHandler {
                cursorShape: Qt.PointingHandCursor
            }
    }

    Text {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#D4D4D4"
        text: qsTr("**Please run this with sudo/admin privileges!**")
    }
}