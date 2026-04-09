import QtQuick

Image {
    id: root

    opacity: buttonMouseArea.containsMouse ? 0.75 : 1
    mipmap: true
    fillMode: Image.PreserveAspectFit

    // custom signal
    signal buttonClicked

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            // on clicking that custom signal will be emitted => TO THE HANDLER THAT IS CONCERNED WITH THAT EVENT --- IN THAT OBJECT ----
            root.buttonClicked();
        }
    }
}
