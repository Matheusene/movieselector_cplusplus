#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <QJsonDocument>
#include <QNetworkAccessManager>

class DownloadHandler : public QObject
{
    Q_OBJECT

public:
    explicit DownloadHandler(QObject *parent = nullptr);
    virtual ~DownloadHandler();
    QByteArray mediaData() const;
    void downloadMediaData(QUrl url);

signals:
    void mediaDataDownloaded();

private slots:
    void dataDownloaded(QNetworkReply* networkReply);

private:
    QNetworkAccessManager       m_networkAccessManager;
    QByteArray                  m_downloadedData;
    QString                     m_downloadFileName;
};

#endif // DOWNLOADHANDLER_H
