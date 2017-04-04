#include "mainwindow.h"
#include <QApplication>

#include <engineTester/maingameloop.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainGameLoop loop;
    loop.start();

    return a.exec();
}
