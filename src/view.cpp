
#include "view.hpp"

#include <QQmlEngine>
#include <QQmlContext>

#include <QDir>

#include <QDebug>

View::View()
{
    setTitle("Qt Quick Little Program");

    setResizeMode(QQuickView::SizeViewToRootObject);

    engine()->addImportPath(":/qml");

    setSource(QStringLiteral("qrc:/qml/View.qml"));

    QObject::connect(this, &View::sceneGraphInitialized,
                     this, &View::initializeGL);
    QObject::connect(this, &View::afterRendering,
                     this, &View::captureFramebuffer);
}

void View::initializeGL()
{
    qDebug() << "Initializing GL";
    initializeOpenGLFunctions();
}

static inline QImage qt_gl_read_framebuffer_rgba8(const QSize &size, bool include_alpha, QOpenGLContext *context)
{
    QOpenGLFunctions *funcs = context->functions();
    const int w = size.width();
    const int h = size.height();
    bool isOpenGL12orBetter = !context->isOpenGLES() && (context->format().majorVersion() >= 2 || context->format().minorVersion() >= 2);
    if (isOpenGL12orBetter) {
        QImage img(size, include_alpha ? QImage::Format_ARGB32_Premultiplied : QImage::Format_RGB32);
        funcs->glReadPixels(0, 0, w, h, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, img.bits());
        return img;
    }

#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    // Without GL_UNSIGNED_INT_8_8_8_8_REV, GL_BGRA only makes sense on little endian.
    const bool supports_bgra = context->isOpenGLES()
            ? context->hasExtension(QByteArrayLiteral("GL_EXT_read_format_bgra"))
            : context->hasExtension(QByteArrayLiteral("GL_EXT_bgra"));
    if (supports_bgra) {
        QImage img(size, include_alpha ? QImage::Format_ARGB32_Premultiplied : QImage::Format_RGB32);
        funcs->glReadPixels(0, 0, w, h, GL_BGRA, GL_UNSIGNED_BYTE, img.bits());
        return img;
    }
#endif
    QImage rgbaImage(size, include_alpha ? QImage::Format_RGBA8888_Premultiplied : QImage::Format_RGBX8888);
    funcs->glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, rgbaImage.bits());
    return rgbaImage;
}


void View::captureFramebuffer()
{
    static int count = 0;
    static QVector<QImage> frames;

    if (++count < 200) {

        qDebug() << "About to capture frame " << count << " " << size();

        // 1. Need to find a way to get framebuffer's color attachment format?
        // 2. Need to figure when this function does.

        QImage image = qt_gl_read_framebuffer_rgba8(size(), false, QOpenGLContext::currentContext()).mirrored(false, true);

        GLenum err;

        while ((err = glGetError()) != GL_NO_ERROR) {
            qDebug() << "OpenGL error: " << err  << endl;
        }

        frames.push_back(image);
    }

    if (count == 200) {

        qDebug() << "About to save all frames " << count;

        QDir d("C:/Build/frames3");
        d.mkdir(".");
        int i = 0;
        for (const QImage &frame: frames) {
            auto name = QString("frame%1.png").arg(i, 3, 10, QChar('0'));
            frame.save(d.filePath(name));
            ++i;
        }
    }
}

