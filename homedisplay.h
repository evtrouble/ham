#ifndef HOMEDISPLAY_H
#define HOMEDISPLAY_H

#include <QString>
#include "mainwindow.h"

class HomeDisplay
{
public:
    HomeDisplay(Ui::MainWindow* ui);

private:
    QString username;
    Ui::MainWindow *ui;
};

#endif // HOMEDISPLAY_H
