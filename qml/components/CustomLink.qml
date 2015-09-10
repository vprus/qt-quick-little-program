import QtQuick 2.4

import Components 1.0

Text {
    signal clicked(var mouse)

    property color normalColor: CustomStyle.linkColor
    property color disabledColor: CustomStyle.linkColorDisabled

    color: enabled ? normalColor : disabledColor
    font: CustomStyle.normalFont

    Behavior on color {
        ColorAnimation { duration: 200 }
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        acceptedButtons: Qt.LeftButton
        enabled: parent.enabled
        onClicked: {
            parent.clicked(mouse);
        }
    }
}
