#ifndef MAINGAMELOOP_H
#define MAINGAMELOOP_H

#include <QObject>
#include <QTimer>

#include <renderEngine/displaymanager.h>
#include <renderEngine/loader.h>
#include <renderEngine/renderer.h>

class MainGameLoop : public QObject
{
    Q_OBJECT
public:
    explicit MainGameLoop(QObject *parent = 0);
    ~MainGameLoop();

    void start();

signals:

private: //slots
    void mainGameLoop();

private:
    DisplayManager mDisplayManager;
    QTimer *mTimer;
    Loader *mLoader;
    Renderer *mRenderer;

};

#endif // MAINGAMELOOP_H
