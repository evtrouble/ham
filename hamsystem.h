#ifndef HAMSYSTEM_H
#define HAMSYSTEM_H

#include <QMainWindow>
#include <QToolButton>
#include <QSystemTrayIcon>

class TasksControl;
class CourseControl;
class HomeDisplay;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class HamSystem : public QMainWindow
{
    Q_OBJECT

public:
    HamSystem(QWidget *parent = nullptr);
    ~HamSystem();

private:
    void navConnect(int id);
    void closeEvent(QCloseEvent *event) override;

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    TasksControl *tasksControl;
    CourseControl *courseControl;
    HomeDisplay *homeDisplay;

    QVector<QToolButton*> btns;
    QSystemTrayIcon *SysIcon;
};
#endif // HAMSYSTEM_H

