#include "netdataaccess.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>

NetDataAccess::NetDataAccess(QWidget* parent) : QWidget(parent), access(new QNetworkAccessManager) {}

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
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]() {
        emit finish(reply);
    });
    return true;
}

bool NetDataAccess::addTaskItem(const QJsonObject& data, int& id)
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
    QNetworkReply::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
            // if(!document.object()["error"].toString().isEmpty()){

            // }
            id = document.object()["id"].toInt();
        } else {
            qWarning() << "Network error:" << reply->errorString();
        }
        reply->deleteLater();
        loop.quit();
    });

    // 阻塞等待网络请求完成
    loop.exec();

    return true;
}

bool NetDataAccess::updateTaskItem(const QJsonObject& data)
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

bool NetDataAccess::deleteTaskItem(const QJsonObject& data)
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

std::unique_ptr<NetDataAccess>& NetDataAccess::instance()
{
    if(dataAccess == nullptr)
    {
        dataAccess = std::unique_ptr<NetDataAccess>(new NetDataAccess);
    }
    return dataAccess;
}

bool NetDataAccess::userLogin(const QJsonObject& data)
{
    QNetworkRequest request;
    QString url = server;
    url += "auth/login/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray _data = QString(QJsonDocument(data).toJson()).toUtf8();
    reply = access->post(request, _data);

    QEventLoop loop;
    // 连接槽函数解析数据
    bool success = false;
    QNetworkReply::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
            // if(!document.object()["error"].toString().isEmpty()){

            // }
            jwt = document.object()["token"].toString();
            success = true;
        } else {
            qWarning() << "Network error:" << reply->errorString();
        }
        reply->deleteLater();
        loop.quit();
    });

    // 阻塞等待网络请求完成
    loop.exec();

    return success;
}

bool NetDataAccess::userRegister(const QJsonObject& data)
{
    QNetworkRequest request;
    QString url = server;
    url += "auth/register/";
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray _data = QString(QJsonDocument(data).toJson()).toUtf8();
    reply = access->post(request, _data);

    // QEventLoop loop;
    // // 连接槽函数解析数据
    // QNetworkReply::connect(reply, &QNetworkReply::finished, [&]() {
    //     if (reply->error() == QNetworkReply::NoError) {
    //         QByteArray _data = reply->readAll();
    //         QJsonParseError parseJsonErr;
    //         QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
    //         // if(!document.object()["error"].toString().isEmpty()){

    //         // }
    //         id = document.object()["id"].toInt();
    //     } else {
    //         qWarning() << "Network error:" << reply->errorString();
    //     }
    //     reply->deleteLater();
    //     loop.quit();
    // });

    // // 阻塞等待网络请求完成
    // loop.exec();

    return true;
}
