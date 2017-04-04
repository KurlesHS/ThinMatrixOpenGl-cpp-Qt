#ifndef MAINGAMELOOP_H
#define MAINGAMELOOP_H

#include <QObject>
#include <QTimer>

#include <renderEngine/renderer.h>
#include <renderEngine/displaymanager.h>

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
    Renderer *mRenderer;
};

#endif // MAINGAMELOOP_H
