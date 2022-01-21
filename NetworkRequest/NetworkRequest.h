#ifndef __NetworkRequest__H__
#define __NetworkRequest__H__

#include <QObject>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
QT_END_NAMESPACE
class NetworkRequest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkRequest(QObject *parent=nullptr);

    void requestString(const QString &uri);

signals:
    void replyRequest(const QString &content);

private:
    QNetworkAccessManager *manager;
};

#endif  //!__NetworkRequest__H__