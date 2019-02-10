#ifndef APIREQUESTMANAGER_H
#define APIREQUESTMANAGER_H

#include <QEventLoop>
#include <QObject>

#include "downloadhandler.h"

class ApiRequestManager : public QObject
{
    Q_OBJECT

public:
    enum RequestType {
        help,
        search,
        type
    };

public:
    explicit ApiRequestManager(QObject *parent = nullptr);
    ~ApiRequestManager();

    void queryRequest(const QString &mediaName, RequestType requestType);

public slots:
    void slotMediaDownloaded();

private:
    DownloadHandler*    m_downloadHandler;
    QEventLoop*         m_eventLoop;
    RequestType             m_requestType;

    static const QString QUERY_URL;
};

#endif // APIREQUESTMANAGER_H
