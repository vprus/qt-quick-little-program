
#pragma once

#include <QQuickView>
#include <QOpenGLFunctions>

class View : public QQuickView, QOpenGLFunctions {
    Q_OBJECT

public:
    View();

private:
    void initializeGL();
    void captureFramebuffer();

};

