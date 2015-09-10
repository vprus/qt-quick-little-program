import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    width: 600
    height: 600

    Canvas {
        id: canvas
        anchors.fill: parent

        property double percentage: 100

        Timer {
            id: timer
            running: true
            interval: 1000
            repeat: true
            onTriggered: {
                if (canvas.percentage == 0) {
                    canvas.percentage = 100;
                } else {
                    canvas.percentage = 0;
                }
            }
        }

        Behavior on percentage {
            NumberAnimation {
            id: animation
            target: canvas
            property: "percentage"
            easing.type: Easing.InQuad
            duration: 400
            }
        }

        onPercentageChanged: {
            requestPaint();
        }

        onPaint: {

            var radius = 170.5;
            var side = 270;
            var stroke = 11;

            var ctx = getContext('2d');

            ctx.save();

            var p1 = percentage/100;
            var p2 = 1.0 - p1;

            ctx.clearRect(0, 0, width, height);

            // Make (0, 0) be the center of the cross.
            ctx.translate(width / 2, height / 2);

            ctx.strokeStyle = "#337ab7"
            ctx.lineWidth = stroke;
            ctx.lineCap = "round";
            ctx.lineJoin = "round";
            ctx.beginPath();

            // Draw the arc starting at 45'. Initially covers 360'
            // and then decreases.
            ctx.arc(0, 0, radius, -0.25 * Math.PI - 2 * Math.PI * percentage/100, -0.25 * Math.PI);

            var c = Math.sqrt(2)/2;
            // The x and y coordinates of the intersection between 45'
            // vector and the circle.
            var cross = Math.sqrt(2)/2*radius;

            // Draw the side of 'x' sign that grows inside from the
            // circle.
            var x = cross * p1 + (-cross) * p2;
            var y = -cross * p1 + cross * p2;
            if (percentage < 0.01) {
                ctx.moveTo(cross - c * stroke * 0.25, -cross + c * stroke * 0.25);
            }

            ctx.lineTo(x, y);

            // Draw the hand of the lens that converts into
            // the other side of the 'x' sign.
            var x1 = side * p1 + cross * p2;
            var y1 = x1;

            var x2 = cross * p1 + (-cross) * p2;
            var y2 = x2;

            ctx.moveTo(x1, y1);
            ctx.lineTo(x2, y2);

            ctx.stroke();

            ctx.restore();
        }

    }

}

