#include "hamsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HamSystem w;
    w.show();
    return a.exec();
}
