
#include "view.hpp"

#include <QQmlEngine>
#include <QQmlContext>

#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

#include <QScreen>

View::View()
{
    setTitle("Qt Quick Little Program");

    setResizeMode(QQuickView::SizeViewToRootObject);

    engine()->addImportPath(":/qml");

    setSource(QStringLiteral("qrc:/qml/View.qml"));

    connect(this, &QQuickView::sceneGraphInitialized,
            this, &View::initializeGL);
    connect(this, &QQuickView::beforeRendering,
            this, &View::switchToFramebuffer);
    connect(this, &QQuickView::afterRendering,
            this, &View::completeFrame);
}

static const char *vertexShaderSource =
    "attribute highp vec4 position;\n"
    "varying mediump vec2 UV;\n"
    "void main() {\n"
    "   UV = position.xy * 0.5 + 0.5;\n"
    "   gl_Position = position;\n"
    "}\n";

static const char *fragmentShaderSource =
    "uniform sampler2D texture;\n"
    "varying mediump vec2 UV;\n"
    "void main() {\n"
    "    gl_FragColor = texture2D(texture, UV);\n"
    "}\n";

void View::initializeGL()
{
    initializeOpenGLFunctions();

    fbo.reset(new QOpenGLFramebufferObject(size()));

    program.reset(new QOpenGLShaderProgram(this));
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();
}

void View::switchToFramebuffer()
{
    // Redirect Qt Quick drawing into scratch framebuffer.
    setRenderTarget(fbo.data());
}

void View::completeFrame()
{
    // At this point we have everything rendered to fbo. We
    // can call QOpenGLFramebufferObject::toImage() to save
    // it, but then we'd rather also show it on the screen.
    // Ideally, we'd use glBlitFramebuffer, but it's not
    // support with ES2, and ANGLE on Windows implements
    // exactly ES2. So, let's try to render to the default
    // framebuffer using fbo's color attachment as texture.
    //
    // Note that it's not really a good overall approach, it's
    // mostly educational excercise.

    // Two triangles making a square.
    static GLfloat vertices[] = {
        -1, 1,
        -1, -1,
        1, 1,
        -1, -1,
        1, 1,
        1, -1
    };

    // Grab texture id of our offscreen framebuffer
    auto texture = fbo->texture();

    // Switch to default framebuffer
    QOpenGLFramebufferObject::bindDefault();

    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    program->bind();

    // Set vertex shader position attribute to our 2 triangles.
    program->setAttributeArray("position", GL_FLOAT, vertices, 2);
    program->enableAttributeArray("position");

    // Set fragment shader texture to one from scratch framebuffer
    glBindTexture(GL_TEXTURE_2D, texture);
    program->setUniformValue("texture", 0);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0])/2);

    program->disableAttributeArray("position");

    program->release();
}
