#include "displaymanager.h"

#include <toolbox/keyboard.h>

namespace  {
const int width = 1280;
const int height = 768;
}

DisplayManager::DisplayManager(QObject *parent) :
    QObject(parent),
    mDisplay(nullptr),
    mRenderer(nullptr)
{

}

DisplayManager::~DisplayManager()
{
    destroyDisplay();
}

void DisplayManager::setRenderer(IRenderer *renderer)
{
    mRenderer = renderer;
    if (mDisplay) {
        mDisplay->setRenderer(renderer);
    }
}

QSize DisplayManager::size() const
{
    return mDisplay->size();
}

void DisplayManager::createDisplay()
{
    if (!mDisplay) {
        Keyboard *keyManager = Keyboard::instance() ;
        mDisplay = new Display();
        mDisplay->installEventFilter(keyManager);
        mDisplay->resize(width, height);
        mDisplay->setRenderer(mRenderer);
        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);
        format.setVersion(3, 2);
        format.setProfile(QSurfaceFormat::CoreProfile);
        mDisplay->setViewPort(QRect(0, 0, height, width));
        mDisplay->show();
    }
}

void DisplayManager::updateDisplay()
{
    if (mDisplay) {
        mDisplay->update();
    }
}

void DisplayManager::destroyDisplay()
{
    if (mDisplay) {
        mDisplay->deleteLater();
        mDisplay = nullptr;
    }
}
