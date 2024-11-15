#include "ClockWidget.h"
#include "ui_hamsystem.h"
#include <QDebug>
ClockWidget::ClockWidget(Ui::MainWindow* ui, QWidget *parent)
    : QWidget(parent), ui(ui), alarmSound(new QSoundEffect(this))
{
    // 设置声音文件路径，使用相对路径
    alarmSound->setSource(QUrl::fromLocalFile("music.ogg"));

    // 连接按钮点击信号到槽函数
    connect(ui->setAlarmBtn, &QPushButton::clicked, this, &ClockWidget::onSetAlarmClicked);
    connect(ui->startCountdownBtn, &QPushButton::clicked, this, &ClockWidget::onStartCountdownClicked);
    connect(ui->stopCountdownBtn, &QPushButton::clicked, this, &ClockWidget::onStopCountdownClicked);
    connect(ui->resetCountdownBtn, &QPushButton::clicked, this, &ClockWidget::onResetCountdownClicked);
    connect(ui->startStopwatchBtn, &QPushButton::clicked, this, &ClockWidget::onStartStopwatchClicked);
    connect(ui->stopStopwatchBtn, &QPushButton::clicked, this, &ClockWidget::onStopStopwatchClicked);
    connect(ui->resetStopwatchBtn, &QPushButton::clicked, this, &ClockWidget::onResetStopwatchClicked);

    // 配置倒计时和计时器的定时器
    countdownTimer.setInterval(20);  // 设置计时器每秒触发一次
    connect(&countdownTimer, &QTimer::timeout, this, &ClockWidget::updateCountdown);

    stopwatchTimer.setInterval(20);  // 计时器每秒更新一次
    connect(&stopwatchTimer, &QTimer::timeout, this, &ClockWidget::updateStopwatch);

    // 设置正计时的QTimeEdit为只读
    ui->stopwatchTimeEdit->setReadOnly(true);
}

void ClockWidget::onSetAlarmClicked()
{
    QDateTime alarmDateTime = ui->alarmTimeEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    if (alarmDateTime < currentDateTime) {
        showNotification("闹钟设置失败，请设置一个合理的时间");
    } else {
        showNotification("闹钟设置成功");
        // 播放一个短暂的成功提示音，如果需要
        // playAlarmSound(); // 可以根据实际情况决定是否在这里播放声音
    }
    qint64 msecToAlarm = currentDateTime.msecsTo(alarmDateTime);
    if (msecToAlarm < 0) {
        msecToAlarm += 24 * 60 * 60 * 1000;  // 如果时间已过，设为明天的此时间
    }
    QTimer::singleShot(msecToAlarm, this, [=]{
        showNotification("闹钟响了！");
        playAlarmSound();  // 播放闹钟声音
    });
}

void ClockWidget::onStartCountdownClicked()
{
    QTime initialTime = ui->countdownTimeEdit->time();

    // 检查初始时间是否有效
    if (initialTime == QTime(0, 0)) {
        showNotification("请设置一个有效的倒计时时间！");
        return;
    }
    remainingTime = initialTime; // 初始化剩余时间

    countdownTimer.start(); // 开始定时器
}


void ClockWidget::onStartStopwatchClicked()
{
    stopwatchTime = QTime(0, 0);  // 重置计时器时间为0
    ui->stopwatchTimeEdit->setTime(stopwatchTime);  // 设置初始时间
    stopwatchTimer.start();
    showNotification("计时开始！");
}

void ClockWidget::updateCountdown()
{
    remainingTime = remainingTime.addSecs(-1); // 每秒减1秒
    ui->countdownTimeEdit->setTime(remainingTime); // 更新 UI 显示



    // 倒计时结束时停止
    if (remainingTime == QTime(0, 0)) {
        countdownTimer.stop();
        showNotification("倒计时结束！");
        playAlarmSound();
    }
}

void ClockWidget::updateStopwatch()
{
    stopwatchTime = stopwatchTime.addSecs(1);
    ui->stopwatchTimeEdit->setTime(stopwatchTime);  // 更新计时器时间
}

void ClockWidget::showNotification(const QString& message)
{
    ui->notificationLabel->setText(message);
    ui->notificationLabel->setVisible(true);

    // 使用QTimer在5秒后将通知标签的文本设置为空字符串
    QTimer::singleShot(5000, this, [=]{
        ui->notificationLabel->setText(""); // 将文本设置为空字符串
    });
}

void ClockWidget::playAlarmSound()
{
    alarmSound->play();
}

void ClockWidget::onStopCountdownClicked()
{
    if (countdownTimer.isActive()) {
        countdownTimer.stop(); // 停止定时器
        showNotification("倒计时已暂停！");
    }
}


void ClockWidget::onResetCountdownClicked()
{
    countdownTimer.stop(); // 停止定时器
    remainingTime = QTime(0, 0); // 重置时间
    ui->countdownTimeEdit->setTime(remainingTime); // 更新 UI
    showNotification("倒计时已重置！");
}

void ClockWidget::onStopStopwatchClicked()
{
    stopwatchTimer.stop();
    showNotification("计时已暂停！");
}

void ClockWidget::onResetStopwatchClicked()
{
    stopwatchTimer.stop();
    stopwatchTime = QTime(0, 0);  // 重置计时器时间为0
    ui->stopwatchTimeEdit->setTime(stopwatchTime);  // 重置显示
    showNotification("计时已重置！");
}
