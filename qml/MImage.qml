import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs

GridLayout {
    property string providerName
    property string rgbColor: "0,0,0"

    columns: 2
    rows: 2

    columnSpacing: 10
    rowSpacing: 10

    anchors.centerIn: parent

    Image {
        Layout.preferredHeight: 200
        Layout.preferredWidth: 200

        source: "image://" + providerName + "/" + rgbColor + "/MImage"

        Rectangle {
            color: "transparent"
            border.width: 3
            border.color: "crimson"
            anchors.fill: parent
        }
    }

    Image {
        Layout.preferredHeight: 200
        Layout.preferredWidth: 200

        source: "image://" + providerName +"/x"

        Rectangle {
            color: "transparent"
            border.width: 3
            border.color: "crimson"
            anchors.fill: parent
        }
    }

    Image {
        Layout.preferredHeight: 200
        Layout.preferredWidth: 200

        source: "image://" + providerName +"/y"

        Rectangle {
            color: "transparent"
            border.width: 3
            border.color: "crimson"
            anchors.fill: parent
        }
    }

    Image {
        Layout.preferredHeight: 200
        Layout.preferredWidth: 200

        source: "image://" + providerName +"/z"

        Rectangle {
            color: "transparent"
            border.width: 3
            border.color: "crimson"
            anchors.fill: parent
        }
    }
}
