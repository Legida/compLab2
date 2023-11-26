import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs

Window {
    id: root

    property variant names: []
    property int current: 0

    width: 640
    height: 480
    visible: false
    title: qsTr("Ранок?")

    Row {
        spacing: 10

        Button {
            text: "save"

            onClicked: fileDialog.open()
        }

        Button {
            text: "prev"

            onClicked: {
                if (root.current > 0) {
                    root.current--
                    firstP.providerName = root.names[root.current]
                }
            }
        }

        Button {
            text: "next"

            onClicked: {
                if (root.current < names.length - 1) {
                    root.current++
                    firstP.providerName = root.names[root.current]
                }
            }
        }
    }

    FolderDialog {
        id: fileDialog
        onAccepted: buttonAdapter.saveClicked(selectedFolder)
    }

    MImage {
        id: firstP
    }

    Component.onCompleted: {
        root.names = handler.getProvidersNames()
        if (names.length >= 1) {
            firstP.providerName = root.names[0]
            root.visible = true
        }
        else {
            console.log("names.len == 0")
        }
    }
}
