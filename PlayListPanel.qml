import QtQuick
import com.company.PlayerController

Rectangle {
    id: root

    property bool hidden: true

    signal searchRequested

    height: 400
    width: 250

    color: "#333333"

    Text {
        id: playlistText

        anchors {
            left: parent.left
            top: parent.top
            margins: 10
        }

        text: "Playlist"
        color: "white"
        font {
            bold: true
            pixelSize: 20
        }
    }

    ListView {
        id: listview

        anchors {
            top: playlistText.bottom
            bottom: addButton.top
            left: parent.left
            right: parent.right
            margins: 20
        }

        clip: true
        // Specifying the QAbstractListModel data source that will feed the data to ListView
        model: PlayerController
        spacing: 10

        // delegate => Defines the template for each item fed from the model
        delegate: Rectangle {
            id: delegate

            // Will be populated with the data fed from the QAbstractListModel class (PlayerController)
            required property string audioTitle
            required property string audioAuthorName
            required property url audioSource
            required property url audioImageSource
            required property url audioVideoSource
            required property int index

            width: listview.width
            height: 50

            color: "#1e1e1e"

            Column {
                id: textsColumn

                anchors {
                    top: parent.top
                    left: parent.left
                    right: removeButton.left
                    margins: 5
                }

                spacing: 5

                Text {
                    width: textsColumn.width
                    elide: Text.ElideRight
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    color: "white"
                    text: delegate.audioTitle

                    font {
                        pixelSize: 14
                        bold: true
                    }
                }

                Text {
                    width: textsColumn.width
                    elide: Text.ElideRight
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 6
                    color: "gray"
                    text: delegate.audioAuthorName

                    font {
                        pixelSize: 10
                    }
                }
            }

            MouseArea {
                id: delegateMouseArea

                anchors.fill: parent

                onClicked: {
                    PlayerController.switchToAudioByIndex(delegate.index);
                }
            }

            ImageButton {
                id: removeButton

                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    rightMargin: 5
                }

                width: 30
                height: 30

                source: "assets/icons/trash_icon.png"

                onButtonClicked: {
                    PlayerController.removeAudio(delegate.index);
                }
            }
        }
    }

    ImageButton {
        id: addButton

        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: 20
        }

        source: "assets/icons/add_icon.png"

        width: 32
        height: 32

        onButtonClicked: {
            root.searchRequested();
            root.hidden = true;
        }
    }

    /*
      Behavior on:
      - A specialized QML object for animation on the property that comes in the on clause
      - You can use it on alomost any numberit or color property
      - The code inside its block is executed when the value of the mentioned property changes
   */
    Behavior on x {
        // The animatio block of code on the proprety
        PropertyAnimation {
            // easing.type => determines the acceleration of the change
            // Easing.InOutQuad => For smooth changes
            easing.type: Easing.InOutQuad
            // 200 ms
            duration: 200
        }
    }
}
