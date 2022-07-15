#include "mainplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPlay w;
    w.show();
    return a.exec();
}
