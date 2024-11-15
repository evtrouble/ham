#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include<QString>
#include <QSoundEffect>  // 包含 QSoundEffect

namespace Ui {
    class MainWindow;
}

class ClockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockWidget(Ui::MainWindow* ui, QWidget* parent = nullptr);

private slots:
    void onSetAlarmClicked();          // 设置闹钟
    void onStartCountdownClicked();    // 启动倒计时
    void onStopCountdownClicked();     // 停止倒计时
    void onResetCountdownClicked();    // 重置倒计时
    void onStartStopwatchClicked();    // 启动计时器
    void onStopStopwatchClicked();     // 停止计时器
    void onResetStopwatchClicked();    // 重置计时器

    void updateCountdown();            // 更新倒计时显示
    void updateStopwatch();            // 更新计时器显示

private:
    Ui::MainWindow* ui;

    QTimer countdownTimer;             // 倒计时定时器
    QTimer stopwatchTimer;             // 计时器定时器
    QTime remainingTime;               // 倒计时的剩余时间
    QTime stopwatchTime;               // 计时器时间
    QSoundEffect* alarmSound;          // 闹钟声音，使用 QSoundEffect

    void showNotification(const QString& message);  // 显示通知信息
    void playAlarmSound();                           // 播放闹钟声音
};

#endif // CLOCKWIDGET_H