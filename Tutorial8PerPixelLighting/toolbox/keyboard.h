#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>
#include <QHash>

class Keyboard : public QObject
{
    Q_OBJECT
public:
    explicit Keyboard(QObject *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);
    bool isKeyPressed(QChar key);
    static Keyboard *instance();

signals:

public slots:

private:
    QHash<int, bool> mKeyTable;
};

#endif // KEYBOARD_H
