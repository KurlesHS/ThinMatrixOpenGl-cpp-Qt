#include "maingameloop.h"

#include <renderEngine/masterrenderer.h>

MainGameLoop::MainGameLoop(QObject *parent) :
    QObject(parent),
    mTimer(new QTimer(this)),    
    mRenderer(nullptr)

{
    connect(mTimer, &QTimer::timeout,
            this, &MainGameLoop::mainGameLoop);

}

MainGameLoop::~MainGameLoop()
{
    mTimer->stop();
    mTimer->deleteLater();
    mDisplayManager.destroyDisplay();

    delete mRenderer;
}

void MainGameLoop::start()
{
    mDisplayManager.createDisplay();
    mRenderer =  new MasterRenderer(&mDisplayManager);
    mDisplayManager.setRenderer(mRenderer);
    mTimer->start(25);
}

void MainGameLoop::mainGameLoop()
{
    mDisplayManager.updateDisplay();
}
