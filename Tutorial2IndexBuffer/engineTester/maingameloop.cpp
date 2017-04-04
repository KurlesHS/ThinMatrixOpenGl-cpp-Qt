#include "maingameloop.h"

MainGameLoop::MainGameLoop(QObject *parent) :
    QObject(parent),
    mTimer(new QTimer(this)),
    mLoader(nullptr),
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
}

void MainGameLoop::start()
{
    mDisplayManager.createDisplay();
    mLoader = new Loader();

    QVector<GLfloat> verticles = {
        -0.5, 0.5, 0.,
        -0.5, -0.5, 0.,
        0.5, -0.5f, 0.,
        0.5, 0.5, 0.
    };

    QVector<GLint> indices = {
        0, 1, 3,
        3, 1, 2
    };

    auto model = mLoader->loadDataToVao(
                verticles,
                indices);

    mRenderer =  new Renderer(model);
    mDisplayManager.setRenderer(mRenderer);

    mTimer->start(25);
}

void MainGameLoop::mainGameLoop()
{
    mDisplayManager.updateDisplay();
}
