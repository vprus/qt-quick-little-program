import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import Components 1.0

Rectangle {
    width: 35 * CustomStyle.normalFont.pixelSize + 12 * 2
    height: 12 * 2 + 18 * CustomStyle.rhythm
    color: Qt.rgba(0, 255, 0, 0)

    objectName: "theRectangle"

    property var style: CustomStyle

    ColumnLayout {

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 12

        spacing: 0

        CustomHeader {
            id: header1
            text: "Qt Quick Little Program"
        }

        CustomLabel {
            objectName: "theLabel"
            id: label1
            text: "This little program demostrates creating custom components in Qt Quick as well as common style defiitions and a baseline grid."
            wrapMode: Text.WordWrap
            Layout.maximumWidth: 35 * CustomStyle.normalFont.pixelSize
        }

        CustomHeader {
            id: header2
            text: "Lorem Ipsum"
        }

        CustomLabel {
            text: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
            wrapMode: Text.WordWrap
            Layout.maximumWidth: 35 * CustomStyle.normalFont.pixelSize
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            CustomLink {
                text: "GitHub"
            }
            CustomLabel {
                text: "\u2022"
            }
            CustomLink {
                text: "Description"
            }
            Item {
                Layout.fillWidth: true
            }

            CustomLink {

                id: settingsLink
                font.family: "FontAwesome"
                font.pixelSize: CustomStyle.rhythm
                text: "\uf013"
            }
        }
    }

    Repeater {
        model: 100
        Rectangle {
            x: 0
            y: 12 + modelData * CustomStyle.rhythm
            z: -1
            height: 1
            width: parent.width
            color: "#eeeeee"
        }
    }


}

