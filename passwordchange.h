#ifndef PASSWORDCHANGE_H
#define PASSWORDCHANGE_H

#include <QDialog>

namespace Ui {
class PassWordChange;
}

class PassWordChange : public QDialog
{
    Q_OBJECT

public:
    explicit PassWordChange(QWidget *parent = nullptr);
    ~PassWordChange();

signals:
    void changePassword(const QString&, const QString&);

private:
    Ui::PassWordChange *ui;
};

#endif // PASSWORDCHANGE_H
