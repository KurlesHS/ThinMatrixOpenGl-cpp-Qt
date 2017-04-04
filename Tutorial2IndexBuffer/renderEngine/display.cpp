#include "display.h"
#include "irenderer.h"

Display::Display(QWidget *parent) :
    QOpenGLWidget(parent),
    mRenderer(nullptr)
{
    mViewPort = rect();
}


void Display::initializeGL()
{
    initializeOpenGLFunctions();

}

void Display::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
    //glViewport(mViewPort.x(), mViewPort.y(), mViewPort.width(), mViewPort.height());
    glViewport(mViewPort.x(), mViewPort.y(), w, h);
}

void Display::setViewPort(const QRectF &viewPort)
{
    mViewPort = viewPort;
}

void Display::setRenderer(IRenderer *renderer)
{
    mRenderer = renderer;
}

void Display::paintGL()
{
    if (mRenderer) {
        mRenderer->render();
    }
}
