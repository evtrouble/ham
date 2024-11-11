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
    bool addTaskItem(QJsonObject&& data, int& id);
    bool updateTaskItem(QJsonObject&& data);
    bool deleteTaskItem(QJsonObject&& data);

    static std::unique_ptr<NetDataAccess>& instance();

private:
    static std::unique_ptr<NetDataAccess> dataAccess;
    std::unique_ptr<QNetworkAccessManager> access;
    QNetworkReply* reply;

signals:
    void finish(QNetworkReply*);
};

#endif // NETDATAACCESS_H
