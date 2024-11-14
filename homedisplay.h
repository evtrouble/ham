#ifndef HOMEDISPLAY_H
#define HOMEDISPLAY_H

#include <QString>
#include "hamsystem.h"

enum class UserType
{
    ADMINISTRATOR,
    ORDINARY
};

class HomeDisplay
{
public:
    HomeDisplay(Ui::MainWindow* ui);
    void setUsername(const QString& username);
    void setuserType(UserType userType);

private:
    Ui::MainWindow *ui;
    UserType userType = UserType::ORDINARY;
};

#endif // HOMEDISPLAY_H
