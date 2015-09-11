
#include "view.hpp"

#include <QQmlEngine>
#include <QQmlContext>

#include <QQmlComponent>
#include <QQuickItem>

#include <QDebug>

View::View()
{
    setTitle("Qt Quick Little Program");

    setResizeMode(QQuickView::SizeViewToRootObject);

    engine()->addImportPath(":/qml");

    connect(this, &QQuickView::statusChanged, [this](QQuickView::Status status) {

        if (status != QQuickView::Ready) {
            return;
        }

        QObject *style = rootObject()->findChild<QObject *>("theStyle");
        qDebug() << "Style: " << style;

        QObject *rectangle = rootObject()->findChild<QObject *>("theRectangle");
        qDebug() << "Rectangle: " << rectangle;

        QObject *header = rootObject()->findChild<QObject *>("theLabel");
        qDebug() << "Label: " << header;
        header->setProperty("color", QColor(255, 0, 0));

        QObject *innerStyle = rootObject()->findChild<QObject *>("innerStyle");
        qDebug() << "Inner style: " << innerStyle;
    });

    setSource(QStringLiteral("qrc:/qml/View.qml"));
}

