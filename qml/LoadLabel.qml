import QtQuick
import QtQuick.Controls
import ".."

Item {
    id: root

    Row {
        anchors.centerIn: parent

        height: lText.height
        spacing: 10

        AnimatedImage {
            height: parent.height
            width: height
            source: "qrc:/compLab2/resources/load.gif"
        }

        Text {
            id: lText
            text: "Loading..."
        }
    }
}
