
#include "view.hpp"

#include <QQmlEngine>
#include <QQmlContext>

View::View()
{
    setTitle("Qt Quick Little Program");

    setResizeMode(QQuickView::SizeViewToRootObject);

    engine()->addImportPath(":/qml");

    setSource(QStringLiteral("qrc:/qml/View.qml"));
}

