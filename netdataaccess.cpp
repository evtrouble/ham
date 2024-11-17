#include "netdataaccess.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QMessageBox>
#include <QUrlQuery>
#include <QFile>
NetDataAccess::NetDataAccess(QWidget *parent) : QWidget(parent), access(new QNetworkAccessManager) {}

std::unique_ptr<NetDataAccess> NetDataAccess::dataAccess = nullptr;
bool NetDataAccess::clearJwt(){
    jwt = "";
}
bool NetDataAccess::exportTable(const QString& model, const QString& dirPath)
{
    QNetworkRequest request;
    QString url = QString("%1export?model=%2&format=csv").arg(server).arg(model);
    request.setUrl(QUrl(url));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());

    QNetworkReply* reply = access->get(request);

    QEventLoop loop;
    bool success = false;

    QObject::connect(reply, &QNetworkReply::finished, this, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            // 保存文件
            QString filePath = dirPath + "/" + model + ".csv";
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                success = true;
            } else {
                qDebug() << "文件打开失败: " << filePath;
            }
        } else {
            qDebug() << "导出失败: " << model << ", 错误: " << reply->errorString();
        }
        reply->deleteLater();
        loop.quit();
    });

    loop.exec(); // 阻塞等待请求完成
    return success;
}

bool NetDataAccess::exportAllTables(const QString& dirPath, QStringList& errors)
{
    QStringList models = {"course", "task", "log", "user", "courseschedule", "studentcourse"};
    errors.clear();

    for (const QString& model : models) {
        if (!exportTable(model, dirPath)) {
            errors.append(model); // 记录失败的表名
        }
    }

    return errors.isEmpty();
}

bool NetDataAccess::loadTaskData()
{
    QNetworkRequest request;
    QString url = server;
    url += "tasks/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());


    QNetworkReply* reply = access->get(request);


    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]()
                           {
                               // 在请求完成后获取状态码
                                QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                               int httpStatus = statusCode.toInt();
                               qDebug() << "LoadTaskData-----HTTP Status Code:" << httpStatus;
                               if (reply->error() == QNetworkReply::NoError) {
                                   // 请求成功
                                   emit TaskFinish(reply);
                               } else {
                                   // 请求失败，输出错误信息
                                   qDebug() << "Network Error:" << reply->errorString();
                                   qDebug() << "Error Code:" << reply->error();
                               }
                           });
    return true;
}

bool NetDataAccess::addTaskItem(const QJsonObject &data, int &id)
{
    QNetworkRequest request;
    QString url = server;
    url += "tasks/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());

    QByteArray _data = QString(QJsonDocument(data).toJson()).toUtf8();
    reply = access->post(request, _data);

    QEventLoop loop;
    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [&]()
                           {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
            // if(!document.object()["error"].toString().isEmpty()){

            // }
            id = document.object()["id"].toInt();
        } else {
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }
        reply->deleteLater();
        loop.quit(); });

    // 阻塞等待网络请求完成
    loop.exec();

    return true;
}

bool NetDataAccess::updateTaskItem(const QJsonObject &data)
{
    QNetworkRequest request;
    QString url = server;
    url += "tasks/" + data["id"].toString();
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());

    QByteArray _data = QString(QJsonDocument(data).toJson()).toUtf8();
    reply = access->put(request, _data);
    return true;
}

bool NetDataAccess::deleteTaskItem(const QJsonObject &data)
{
    QNetworkRequest request;
    QString url = server;
    url += "tasks/" + data["id"].toString();
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());

    reply = access->deleteResource(request);

    return true;
}

std::unique_ptr<NetDataAccess> &NetDataAccess::instance()
{
    if (dataAccess == nullptr)
    {
        dataAccess = std::unique_ptr<NetDataAccess>(new NetDataAccess);
    }
    return dataAccess;
}

bool NetDataAccess::userLogin(const QString &username, const QString &password, bool &isAdmin)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    QNetworkRequest request;
    QString url = server;
    url += "auth/login/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray data = QString(QJsonDocument(json).toJson()).toUtf8();
    QNetworkReply* reply = access->post(request, data);

    QEventLoop loop;

    // 连接槽函数解析数据
    bool success = false;
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [&]()
                           {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
            QVariant stateCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if(!stateCode.isValid())return;
            if(stateCode.toInt() == 200){
                auto obj = document.object();
                jwt = obj["token"].toString();
                isAdmin = obj["user"].toObject()["isAdmin"].toBool();
                success = true;
                emit loginSuccess();

            } else {
                QMessageBox::critical(this, "error!", document.object()["error"].toString());
            }
        } else {
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }
        reply->deleteLater();
        loop.quit(); });

    // 阻塞等待网络请求完成
    loop.exec();

    return success;
}

bool NetDataAccess::userRegister(const QString &username, const QString &password, const QString &email)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    json["email"] = email;

    QNetworkRequest request;
    QString url = server;
    url += "auth/register/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray data = QString(QJsonDocument(json).toJson()).toUtf8();
    QNetworkReply* reply = access->post(request, data);

    QEventLoop loop;
    // 连接槽函数解析数据
    bool success = false;
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [&]()
                           {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
            QVariant stateCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if(!stateCode.isValid())return;
            if(stateCode.toInt() == 201) success = true;
            else {
                QMessageBox::critical(this, "error!", document.object()["error"].toString());
            }
        } else {
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }
        reply->deleteLater();
        loop.quit(); });

    // 阻塞等待网络请求完成
    loop.exec();

    return success;
}

bool NetDataAccess::changePassword(const QString &old_password, const QString &new_password)
{
    QJsonObject json;
    json["oldPassword"] = old_password;
    json["newPassword"] = new_password;

    QNetworkRequest request;
    QString url = server;
    url += "auth/change-password/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray data = QString(QJsonDocument(json).toJson()).toUtf8();
    QNetworkReply* reply = access->post(request, data);

    QEventLoop loop;
    // 连接槽函数解析数据
    bool success = false;
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [&]()
                           {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
            QVariant stateCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if(!stateCode.isValid())return;
            if(stateCode.toInt() == 201) success = true;
            else {
                QMessageBox::critical(this, "error!", document.object()["error"].toString());
            }
        } else {
            QMessageBox::critical(this, "Network error!", reply->errorString());
        }
        reply->deleteLater();
        loop.quit();
    });

    // 阻塞等待网络请求完成
    loop.exec();

    return success;
}

bool NetDataAccess::getPersonalCourse(int week)
{
    QNetworkRequest request;
    QString url = server;
    url += "schedule/weekly/";
    QUrl url_temp(url);
    if (week >= 0)
    {
        QUrlQuery query;
        query.addQueryItem("week", QString::number((week)));
        url_temp.setQuery(query.query());
    }
    request.setUrl(url_temp);

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());
    QNetworkReply* reply = access->get(request);
    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]()
                           { emit personalCourseFinish(reply); });
    return true;
}
bool NetDataAccess::getCurrentWeek()
{
    QNetworkRequest request;
    QString url = server;
    url += "schedule/current-week/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());
    QNetworkReply* reply = access->get(request);
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]()
                           { emit finish(reply); });
    return true;
}
bool NetDataAccess::searchCourse(
    const int academicYear,
    const int semester,
    const QString& instructor,
    const QString& name,
    const QString& department,
    const int hasCapacity
    )
{
    qDebug()<<"hasCapacity"<<" "<<hasCapacity;

    QNetworkRequest request;
    QString url = server;
    url += "schedule/search/";

    QUrlQuery query;

    // Skip default/placeholder values
    if (academicYear > 0) {
        query.addQueryItem("academicYear", QString::number(academicYear));
    }
    if (semester != 0) {
        query.addQueryItem("semester", QString::number(semester));
    }
    if (!instructor.isEmpty() && instructor != "请选择教师") {
        query.addQueryItem("instructor", instructor);
    }
    if (!name.isEmpty() && name != "请输入课程名") {
        query.addQueryItem("name", name);
    }
    if (!department.isEmpty() && department != "请选择院系") {
        query.addQueryItem("department", department);
    }
    qDebug()<<"hasCapacity"<<" "<<hasCapacity;

    if (hasCapacity != -1) {
        query.addQueryItem("hasCapacity", hasCapacity == 1 ? "true" : "false");
    }
    QUrl urlWithQuery(url);
    qDebug()<<"query"<<query.toString();
    if (!query.isEmpty()) {
        urlWithQuery.setQuery(query);
    }
    request.setUrl(urlWithQuery);

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());

    QNetworkReply* reply = access->get(request);

    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]() {
        emit schoolCourseFinish(reply);
    });

    return true;
}
