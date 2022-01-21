#ifndef __QuickTemplateObject__H__
#define __QuickTemplateObject__H__

#include <QObject>

QT_BEGIN_NAMESPACE
class NetworkRequest;
class QtPrivateDeclar;
QT_END_NAMESPACE
class QuickTemplateObject : public QObject
{
    Q_OBJECT
public:
    explicit QuickTemplateObject(QObject *parent=nullptr);

    void requestRelease(const QString &url);
    void requestReleases(const QString &url);

signals:
    void loaded(QtPrivateDeclar *declar);

private:
    NetworkRequest *request;
};

#endif  //!__QuickTemplateObject__H__