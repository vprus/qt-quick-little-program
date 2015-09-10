
pragma Singleton

import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls.Private 1.0

// Singleton item that defines all the styles
//
// The most important are font sizes.
// Normal font is 10.5 points, or 14 pixels at 96 dpi.
// Leading is x1.5, or 21 pixels
// Header font is 16.5 points, or 22 pixels. The default
// leading is x1.4/30 there, which we don't really change
// since headers are never multi-line. For headers, we
// margins on top and bottom to make header height equal
// to double normal line leading.
//
// See https://wiki.qt.io/Qml_Styling for background
Item {

    FontLoader {
        source: "fontawesome-webfont.ttf"
    }

    property FontMetrics normalFontMetrics: FontMetrics {
        id: normalFontMetrics
        font.family: "Segoe UI"
        font.pointSize: 10.5
    }

    property double normalFontSpacing: 1.5

    // There is no obvious way to create font instance in QML,
    // therefore we steal the one that FontMetrics creates.
    property font normalFont: normalFontMetrics.font

    property FontMetrics headerFontMetrics: FontMetrics {
        id: headerFontMetrics
        font.family: "Segoe UI"
        font.pointSize: 16.5
    }

    property font headerFont: headerFontMetrics.font

    property int rhythm: normalFontSpacing * normalFont.pixelSize

    property color normalColor: "#333333"
    property color headerColor: "#337ab7"

    property color linkColor: "#337ab7"
    property color linkColorDisabled: "#999ba4"

    // Converts pixels at 96 DPI to pixels at current logical DPI.
    function dp( x ) {
        // It would seem that Screen.devicePixelRatio should do the
        // same, but in practice, it appears to be always 1.0
        return Math.round( x * Settings.dpiScaleFactor );
    }

    function pixelsFromPoints(points) {
        var inches = points / 72;
        var pixels = inches * 96;
        return dp(pixels);
    }

    function dialogMargin() {
        return dp(12)
    }

    Component.onCompleted: {
        console.log("Custom style is loaded.")
        console.log("Normal font size and spacing: "
                    + normalFont.pixelSize + ", " + normalFontMetrics.lineSpacing);
        console.log("Header font size and spacing: "
                    + headerFont.pixelSize + ", " + headerFontMetrics.lineSpacing);
        console.log("Vertical grid step: " + rhythm)
    }
}
