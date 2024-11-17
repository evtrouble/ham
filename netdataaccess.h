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
    bool getCurrentWeek();

    bool getPersonalCourse(int week = 1);
    bool searchCourse(const int academicYear = -1,
                      const int semester = -1,
                      const QString& instructor = QString(),
                      const QString& name = QString(),
                      const QString& department = QString(),
                      const int hasCapacity = -1
                      );
    QString getJwt() const { return jwt; }
    bool clearJwt();
    static std::unique_ptr<NetDataAccess>& instance();

private:
    static std::unique_ptr<NetDataAccess> dataAccess;
    std::unique_ptr<QNetworkAccessManager> access;
    QNetworkReply* reply;
    QNetworkReply* nreply;

    QString jwt;

signals:
    // void initFinish(QNetworkReply*);
    void TaskFinish(QNetworkReply* reply);
    void personalCourseFinish(QNetworkReply *reply);
    void schoolCourseFinish(QNetworkReply *reply);
    void finish(QNetworkReply *reply);
    void loginSuccess();  // 新增登录成功信号

    void tokenError();
};

#endif // NETDATAACCESS_H
