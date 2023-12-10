import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls

Row {
    id: root
    property variant mImage: null
    property variant names: []
    property int current: 0

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
                mImage.providerName = root.names[root.current]
            }
        }
    }

    Button {
        text: "next"

        onClicked: {
            if (root.current < names.length - 1) {
                root.current++
                mImage.providerName = root.names[root.current]
            }
        }
    }

    Text {
        text: "images count: " + root.names.length
    }

    //Row {
    //    spacing: 3

    //    SpinBox {
    //        editable: true
    //        id: r
    //        to: 255
    //        from: 0
    //    }

    //    SpinBox {
    //        editable: true
    //        id: g
    //        to: 255
    //        from: 0
    //    }

    //    SpinBox {
    //        editable: true
    //        id: b
    //        to: 255
    //        from: 0
    //    }
    //}

    //Button {
    //    text: "color"

    //    onClicked: {
    //        mImage.rgbColor = r.value + "," + g.value + "," + b.value
    //    }
    //}

    FolderDialog {
        id: fileDialog
        onAccepted: handler.saveImage(mImage.providerName, selectedFolder)
    }

    Connections {
        target: handler
        onProviderCountChanges: {
            root.names = handler.getProvidersNames()
        }
    }
}
