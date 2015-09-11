
#include "view.hpp"

#include <QQmlEngine>
#include <QQmlContext>

#include <QQmlComponent>

View::View()
{
    setTitle("Qt Quick Little Program");

    setResizeMode(QQuickView::SizeViewToRootObject);

    engine()->addImportPath(":/qml");

    QQmlComponent component(engine());
    const char *source =
            "import QtQuick 2.0\n"
            "import Components 1.0\n"
            "QtObject {\n"
            "    property var style: CustomStyle\n"
            "    function setColor(c) { CustomStyle.headerColor = c; }\n"
            "}";
    component.setData(source, QUrl());
    QObject *item = component.create();
    QObject *style = qvariant_cast<QObject*>(item->property("style"));
    style->setProperty("headerColor", QColor(255, 0, 0));

    setSource(QStringLiteral("qrc:/qml/View.qml"));
}

