#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <QObject>

#include "display.h"

class IRenderer;

class DisplayManager : public QObject
{
    Q_OBJECT
public:
    explicit DisplayManager(QObject *parent = 0);
    ~DisplayManager();

    void setRenderer(IRenderer *renderer);

    void createDisplay();
    void updateDisplay();
    void destroyDisplay();

signals:

public slots:

private:
    Display *mDisplay;
    IRenderer *mRenderer;

};

#endif // DISPLAYMANAGER_H
