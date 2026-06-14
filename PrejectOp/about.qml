import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Item {
    FontLoader {
        id: monty
        source: "fonts/mont.ttf"
    }
    Rectangle {
            width: parent.width
            height: parent.height
            color: "#292929"
    }

    Image {
        id: name
        source: "Images/anime.png"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: 200
        height: 200

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
    }
    Text {
        color: "#fefefe"
        font.pixelSize: 25
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 75
        anchors.leftMargin: 20
        font.family: monty.font
        text: "About:"
    }
    Text {
        color: "#fefefe"
        font.family: monty.font
        text: qsTr("Hi! This app is made by JQx_99.")
        anchors.leftMargin: 20
        anchors.topMargin: 125
        anchors.left: parent.left
        anchors.top: parent.top
    }
    Text {
        color: "#fefefe"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 150
        font.family: monty.font
        text: qsTr("My full name/ government name is Saradendu Palei.")
    }
    Text {
        color: "#fefefe"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 175
        font.family: monty.font
        text: qsTr("I was very annoyed by the fact that my fingerprint sensor won't work on Linux.")
    }
    Text {
        color: "#fefefe"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 200
        font.family: monty.font
        text: qsTr("So I made it work!")
    }
    Text {
        color: "#fefefe"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 225
        font.family: monty.font
        text: qsTr("Enjoy! If you happen to have some errors please mail me at <a href='mailto:bdservo7@gmail.com'>bdservo7@gmail.com</a>.")
        textFormat: Text.RichText
        onLinkActivated: (link) => {
                Qt.openUrlExternally(link)
            }
    }
    Text {
        font.family: monty.font
        text: "I live in India. 🇮🇳"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 250
        color: "#fefefe"
    }
    Text {
        font.family: monty.font
        text: "<a href='https://github.com/JQx-999'>Visit my GitHub Profile!</a>"
        textFormat: Text.RichText
        onLinkActivated: (link) => {
                Qt.openUrlExternally(link)
            }
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 275
    }
}
