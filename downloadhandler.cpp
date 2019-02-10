#include <QNetworkReply>
#include <QNetworkRequest>

#include "downloadhandler.h"

DownloadHandler::DownloadHandler(QObject *parent) :
    QObject(parent)
{
    connect(&m_networkAccessManager, SIGNAL (finished(QNetworkReply*)), this, SLOT (dataDownloaded(QNetworkReply*)));
}

DownloadHandler::~DownloadHandler() { }

void DownloadHandler::downloadMediaData(QUrl url)
{
    QNetworkRequest request(url);
    m_networkAccessManager.get(request);
}

void DownloadHandler::dataDownloaded(QNetworkReply* networkReply)
{
    if (networkReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Unable to complete the request due to a network error.";
        return;
    }

    m_downloadedData = networkReply->readAll();

    networkReply->deleteLater();

    emit mediaDataDownloaded();
}

QByteArray DownloadHandler::mediaData() const
{
    return m_downloadedData;
}
