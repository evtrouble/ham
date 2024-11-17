#ifndef HAMSYSTEM_H
#define HAMSYSTEM_H

#include <QMainWindow>
#include <QToolButton>
#include <QSystemTrayIcon>

class TasksControl;
class CourseControl;
class HomeDisplay;
class ClockWidget;

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
    void logout();
private:
    void navConnect(int id);
    void closeEvent(QCloseEvent *event) override;
    void setupLoginUI();
    void setupNavigationButtons();
    void initializeSystem();
    void setupTrayIcon();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void resetUIState();
    void resetControllers();

private:
    Ui::MainWindow *ui;
    TasksControl *tasksControl;
    CourseControl *courseControl;
    HomeDisplay *homeDisplay;
    ClockWidget *clockWidget;

    QVector<QToolButton*> btns;
    QSystemTrayIcon *SysIcon;
};
#endif // HAMSYSTEM_H
