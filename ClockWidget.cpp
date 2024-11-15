#include "ClockWidget.h"
#include "ui_hamsystem.h"

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
    countdownTimer.setInterval(1000);  // 倒计时每秒更新一次
    connect(&countdownTimer, &QTimer::timeout, this, &ClockWidget::updateCountdown);

    stopwatchTimer.setInterval(1000);  // 计时器每秒更新一次
    connect(&stopwatchTimer, &QTimer::timeout, this, &ClockWidget::updateStopwatch);
}

void ClockWidget::onSetAlarmClicked()
{
    QDateTime alarmDateTime = ui->alarmTimeEdit->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
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
    remainingTime = ui->countdownTimeEdit->time();
    countdownTimer.start();
}

void ClockWidget::onStartStopwatchClicked()
{
    stopwatchTime = QTime(0, 0);  // 重置计时器时间为0
    ui->stopwatchTimeEdit->setTime(stopwatchTime);  // 设置初始时间
    stopwatchTimer.start();
}

void ClockWidget::updateCountdown()
{
    if (remainingTime == QTime(0, 0)) {
        countdownTimer.stop();
        showNotification("倒计时结束！");
        playAlarmSound();  // 播放闹钟声音
    } else {
        remainingTime = remainingTime.addSecs(-1);
        ui->countdownTimeEdit->setTime(remainingTime);  // 更新 QTimeEdit 控件的时间
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
    ui->notificationLabel->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    ui->notificationLabel->setVisible(true);
    QTimer::singleShot(5000, this, [=]{
        ui->notificationLabel->setVisible(false);
    });
}

void ClockWidget::playAlarmSound()
{
    alarmSound->play();
}

void ClockWidget::onStopCountdownClicked()
{
    countdownTimer.stop();
}

void ClockWidget::onResetCountdownClicked()
{
    countdownTimer.stop();
    remainingTime = ui->countdownTimeEdit->time();
    ui->countdownTimeEdit->setTime(remainingTime);
}

void ClockWidget::onStopStopwatchClicked()
{
    stopwatchTimer.stop();
}

void ClockWidget::onResetStopwatchClicked()
{
    stopwatchTimer.stop();
    stopwatchTime = QTime(0, 0);  // 重置计时器时间为0
    ui->stopwatchTimeEdit->setTime(stopwatchTime);  // 重置显示
}
