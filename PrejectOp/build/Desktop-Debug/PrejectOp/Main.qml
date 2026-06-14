import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Window {
    minimumWidth: 640
    minimumHeight: 480
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth
    visible: true
    title: qsTr("ELAN 0c00 support")
    Material.theme: Material.Light
    FontLoader {
            id: jbm
            source: "fonts/JetBrainsMono-VariableFont_wght.ttf"
        }


    Rectangle {
            width: parent.width
            height: parent.height
            color: "#292929"
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: MainMenu {}
    }
}