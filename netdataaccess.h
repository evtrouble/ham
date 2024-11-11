#ifndef NETDATAACCESS_H
#define NETDATAACCESS_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWidget>

class NetDataAccess : public QWidget
{
    Q_OBJECT
private:
    NetDataAccess(QWidget* parent = nullptr);

    constexpr static char server[] = "http://localhost:3000/";

public:
    bool loadTaskData();
    bool addTaskItem(const QJsonObject& data, int& id);
    bool updateTaskItem(const QJsonObject& data);
    bool deleteTaskItem(const QJsonObject& data);

    bool userLogin(const QJsonObject& data);
    bool userRegister(const QJsonObject& data);

    static std::unique_ptr<NetDataAccess>& instance();

private:
    static std::unique_ptr<NetDataAccess> dataAccess;
    std::unique_ptr<QNetworkAccessManager> access;
    QNetworkReply* reply;
    QString jwt;

signals:
    void finish(QNetworkReply*);
    void tokenError();
};

#endif // NETDATAACCESS_H
