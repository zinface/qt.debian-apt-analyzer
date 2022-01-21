#include "NetworkRequest.h"
#include <QNetworkAccessManager>
#include <qnetworkreply.h>

NetworkRequest::NetworkRequest(QObject *parent) : QObject(parent) 
, manager(new QNetworkAccessManager)
{
    connect(manager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply){
        emit replyRequest(reply->readAll());
    });
}

void NetworkRequest::requestString(const QString &uri) {
    manager->get(QNetworkRequest(QUrl(uri)));
}