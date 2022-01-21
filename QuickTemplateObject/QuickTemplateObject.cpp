#include "QuickTemplateObject.h"

#include <NetworkRequest.h>
#include <QtPrivateDeclar.h>

QuickTemplateObject::QuickTemplateObject(QObject *parent) : QObject(parent)
, request(new NetworkRequest)
{
    connect(request, &NetworkRequest::replyRequest,[=](const QString &content){
        QtPrivateDeclar *declar = new QtPrivateDeclar;
        declar->setContent(content);
        emit loaded(declar);
    });
}

void QuickTemplateObject::requestRelease(const QString &url) {
    request->requestString(url);
}