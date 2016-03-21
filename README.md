
# Qt Quick: Frame Grabber Option 1

This program demostrates how to grab each frame that
`QQuickWindow` generates. We basically connect to
`QQuickWindow::afterRendering` and read pixels into a `QImage`.

There's a convenient `QOpenGLFramebufferObject::toImage` method,
but sadly, one can neither get an instance of this object corresponding
to the default framebuffer, nor create an instance passing raw OpenGL
framebuffer id. Therefore, the best approach is to just copy-paste
the implementation of `toImage` method.
