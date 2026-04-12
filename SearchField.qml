import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    // Mapped with the signal searchInput.accepted
    signal accepted(string value)

    color: "#1e1e1e"
    border.color: searchInput.activeFocus ? Qt.lighter("#5F8575") : "transparent"
    border.width: 1

    // if enabled (allowed to receive an input)
    opacity: enabled ? 1 : 0.6

    TextInput {
        id: searchInput

        anchors.fill: parent

        font.pixelSize: 14
        color: "white"

        leftPadding: 30
        // Aligning the text at the center of the parent (vertically)
        verticalAlignment: TextInput.AlignVCenter

        Image {
            anchors {
                left: parent.left
                leftMargin: 5
                verticalCenter: parent.verticalCenter
            }

            width: 16
            height: 16

            mipmap: true
            source: "assets/icons/search_icon.png"
        }

        // Custom handler of the signal accepted that is emitted when the enter key is pressed
        onAccepted: {
            root.accepted(text);
        }
    }
}
