#include <QApplication>

#include "MainWidget.h"

#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Start \"Program\"";

    MainWidget w;
    w.show();

    return a.exec();
}