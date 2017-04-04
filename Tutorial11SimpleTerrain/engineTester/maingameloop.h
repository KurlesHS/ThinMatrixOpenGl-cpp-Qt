#ifndef MAINGAMELOOP_H
#define MAINGAMELOOP_H

#include <QObject>
#include <QTimer>

#include <renderEngine/entityrenderer.h>
#include <renderEngine/displaymanager.h>

class MasterRenderer;

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
    MasterRenderer *mRenderer;
};

#endif // MAINGAMELOOP_H
