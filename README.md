
# Qt Quick: Frame Grabber Option 2

This program an alternative approach to grab each frame that
QQuickWindow generates:

- Create a `QOpenGLFramebufferObject` to use a side buffer.

- Use `QQuickWindow::setRenderTarget` is called to redirect rendering to
  that buffer.

- Connect to `QQuickWindow::afterRendering`. Every time we're called, our
  buffer will have entire frame that we can save. We will also need to
  copy that frame to the window framebuffer.

It is not the best overall approach, since we need to allocate this
extra framebuffer and copy from it to window framebuffer, and we still
need to read all pixels from GL if we want to save them. See
[Option 1](https://github.com/vprus/qt-quick-little-program/tree/frame-grabber-1)
for a more direct design.

However, this example does show how one can portably copy between
framebuffers in Qt. One could imagine `glBlitFramebuffer` to be sufficient,
but it's not supported in ES2, and the ANGLE library that Qt often uses on
Windows implements exactly ES2. Therefore, this examples renders into
window framebuffer using our scratch framebuffer as texture - and shows
some of the conveniences that `QOpenGLShaderProgram` provides.
