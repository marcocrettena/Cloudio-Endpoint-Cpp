#include "controllerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);

    ControllerWindow w;
    w.show();

    return a.exec();
}

