#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <QDialog>

namespace Ui {
class RegisterUser;
}

class RegisterUser : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterUser(QWidget *parent = nullptr);
    ~RegisterUser();

signals:
    void registerUser(const QString&, const QString&, const QString&);

private:
    Ui::RegisterUser *ui;
};

#endif // REGISTERUSER_H
