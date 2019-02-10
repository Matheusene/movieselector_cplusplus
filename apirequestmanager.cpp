#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "apirequestmanager.h"

const QString ApiRequestManager::QUERY_URL = "http://www.omdbapi.com/?apikey=90d02ef3&t=";

ApiRequestManager::ApiRequestManager(QObject *parent) :
    QObject(parent),
    m_requestType(help)
{
    m_eventLoop = new QEventLoop();

    m_downloadHandler = new DownloadHandler();
    connect(m_downloadHandler, SIGNAL(mediaDataDownloaded()), this, SLOT(slotMediaDownloaded()));
}

ApiRequestManager::~ApiRequestManager()
{
    delete m_downloadHandler;
    delete m_eventLoop;
}

void ApiRequestManager::queryRequest(const QString& mediaName, RequestType requestType)
{
    QUrl mediaURL = QUrl(QUERY_URL + mediaName);
    m_downloadHandler->downloadMediaData(mediaURL);
    m_requestType = requestType;
    m_eventLoop->exec();
}

void ApiRequestManager::slotMediaDownloaded()
{
    m_eventLoop->quit();
    QJsonDocument json = QJsonDocument::fromJson(m_downloadHandler->mediaData());

    if (json.isObject())
    {
        QJsonObject mediaJson = json.object();
        QStringList mediaKeys = mediaJson.keys();

        if (m_requestType == search)
        {
            for (int i = 0; i < mediaKeys.size(); ++i)
            {
                qDebug() << mediaKeys.at(i) << " - " << mediaJson[mediaKeys.at(i)].toString();
            }
        }
        else if (m_requestType == type)
        {
            qDebug() << "Type - " << mediaJson["Type"].toString();
        }
        else
        {
            qDebug() << "Request type unrecognized.";
        }
    }
}
