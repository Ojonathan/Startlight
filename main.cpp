#include "mainwindow.h"
#include "gameview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Qt::WindowFlags flags = 0;
    //flags |= Qt::CustomizeWindowHint;
    //flags |= Qt::WindowTitleHint;
    //w.setWindowFlags(flags);
    w.show();

    return a.exec();
}
