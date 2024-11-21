#include "hamsystem.h"
#include <QDir>
#include<QProcess>
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HamSystem w;
    w.show();

    return a.exec();
}
