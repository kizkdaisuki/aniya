#include "mainplay.h"
#include "creater.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainPlay w;
    creater c;
    return a.exec();
}
