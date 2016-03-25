
#pragma once

#include <QQuickView>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

#include <QScopedPointer>

class View : public QQuickView, protected QOpenGLFunctions {
    Q_OBJECT

public:
    View();

protected:
    void initializeGL();
    void switchToFramebuffer();
    void completeFrame();

    QScopedPointer<QOpenGLFramebufferObject> fbo;
    QScopedPointer<QOpenGLShaderProgram> program;
};

