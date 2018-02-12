#include "rubikclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RubikClock w;
    w.show();

    return a.exec();
}
