#include "keyboard.h"

#include <QKeyEvent>
#include <QDebug>

Keyboard::Keyboard(QObject *parent) : QObject(parent)
{

}

bool Keyboard::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::KeyPress:
    case QEvent::KeyRelease: {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        mKeyTable[keyEvent->key()] = event->type() == QEvent::KeyPress;                
    }
        break;
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}

bool Keyboard::isKeyPressed(QChar key)
{
    key = key.toUpper();
    return mKeyTable.value(key.toLatin1(), false);
}

Q_GLOBAL_STATIC(Keyboard, glob_instance)
Keyboard *Keyboard::instance()
{
    return glob_instance;
}
