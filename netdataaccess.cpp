#include "netdataaccess.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>

NetDataAccess::NetDataAccess(QWidget* parent) : QWidget(parent), access(new QNetworkAccessManager) {}

std::unique_ptr<NetDataAccess> NetDataAccess::dataAccess = nullptr;

bool NetDataAccess::loadData()
{
    QNetworkRequest request;
    request.setUrl(QUrl(server));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));
    reply = access->get(request);
    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, this, [=]() {
        emit finish(reply);
    });
    return true;
}

bool NetDataAccess::addItem(QJsonObject&& data, int& id)
{
    QNetworkRequest request;
    request.setUrl(QUrl(server));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray _data = QString(QJsonDocument(data).toJson()).toUtf8();
    reply = access->post(request, _data);

    QEventLoop loop;
    // 连接槽函数解析数据
    QNetworkReply::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray _data = reply->readAll();
            QJsonParseError parseJsonErr;
            QJsonDocument document = QJsonDocument::fromJson(_data, &parseJsonErr);
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

bool NetDataAccess::updateItem(QJsonObject&& data)
{
    QNetworkRequest request;
    QString url = server;
    url += "/" + data["id"].toString();
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QByteArray _data = QString(QJsonDocument(data).toJson()).toUtf8();
    reply = access->put(request, _data);
    return true;
}

bool NetDataAccess::deleteItem(QJsonObject&& data)
{
    QNetworkRequest request;
    QString url = server;
    url += "/" + data["id"].toString();
    request.setUrl(QUrl(url));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

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
