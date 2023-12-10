import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Ранок?")

    ColumnLayout {
        anchors.fill: parent

        Header {
            Layout.fillWidth: true
            mImage: image
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            MImage {
                id: image
                visible: false
            }

            LoadLabel {
                anchors.fill: parent
                id: label
                visible: true
            }

            Connections {
                target: handler
                onProviderCountChanges: {
                    if (providerCount > 0) {
                        label.visible = false
                        image.visible = true
                        image.providerName = handler.getProvidersNames()[0]
                        console.log("test")
                    }
                }
            }
        }
    }
}
