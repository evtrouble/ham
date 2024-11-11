#ifndef HOMEDISPLAY_H
#define HOMEDISPLAY_H

#include <QString>
#include "mainwindow.h"

class HomeDisplay
{
public:
    HomeDisplay(Ui::MainWindow* ui);
    void setUsername(const QString& username);

private:
    Ui::MainWindow *ui;
};

#endif // HOMEDISPLAY_H
