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

    bool userLogin(const QString& username, const QString& password, bool& isAdmin);
    bool userRegister(const QString& username, const QString& password, const QString& email);
    bool changePassword(const QString& old_password, const QString& new_password);

    bool getPersonalCourse(int week = -1);

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
