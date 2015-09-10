TEMPLATE = app

QT += qml quick widgets

SOURCES += \
    src/view.cpp \
    src/main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/view.hpp

DISTFILES += \
    qml/components/qmldir
