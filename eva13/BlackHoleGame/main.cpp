
#include "blackholewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackHoleWidget w;
    w.show();

    return a.exec();
}

