
import QtQuick 2.0
import QtQuick.Layouts 1.1

import Components 1.0

ColumnLayout {

    id: root
    property string text

    spacing: 0

    Item {
        id: marginTop
        Layout.minimumHeight: (2 * CustomStyle.rhythm - textDisplay.height)/2
        Layout.minimumWidth: 1
    }

    Text {
        id: textDisplay
        text: root.text
        font: CustomStyle.headerFont
        color: CustomStyle.headerColor
    }

    Item {
        id: marginBottom
        Layout.minimumHeight: (2 * CustomStyle.rhythm - textDisplay.height)/2
        Layout.minimumWidth: 1
    }
}
