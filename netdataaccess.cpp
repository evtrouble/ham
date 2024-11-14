#include "netdataaccess.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QMessageBox>
#include <QUrlQuery>

NetDataAccess::NetDataAccess(QWidget *parent) : QWidget(parent), access(new QNetworkAccessManager) {}

std::unique_ptr<NetDataAccess> NetDataAccess::dataAccess = nullptr;

bool NetDataAccess::loadTaskData()
{
    QNetworkRequest request;
    QString url = server;
    url += "tasks/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", "Bearer " + jwt.toUtf8());
    reply = access->get(request);
    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]()
                           { emit finish(reply); });
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
    reply = access->post(request, data);

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
    reply = access->post(request, data);

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
    reply = access->post(request, data);

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
    reply = access->get(request);
    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]()
                           { emit finish(reply); });
    return true;
}
