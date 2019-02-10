#include <QCoreApplication>
#include <QDebug>
#include <QJsonObject>
#include <QString>

#include "apirequestmanager.h"

void showMenu()
{
    qDebug() << "\n\t-h\t--help";
    qDebug() << "\t\tPrint the application options.";
    qDebug() << "\n\t-s\t--search <MEDIA TITLE>";
    qDebug() << "\t\tSearch for the media title.";
    qDebug() << "\n\t-t\t--type <MEDIA TITLE>";
    qDebug() << "\t\tReturns the selected media type. (movie, series, episode)\n";
}

QString getMediaTitle(QStringList arguments)
{
    QString mediaTitle;
    for (int i = 2; i < arguments.size(); ++i)
    {
        mediaTitle.append(arguments.at(i) + " ");
    }
    return mediaTitle;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ApiRequestManager apiManager;

    if (argc > 1)
    {
        if ((strcmp("-h", argv[1]) == 0) || (strcmp("--help", argv[1]) == 0))
        {
            showMenu();
        }
        else if ((strcmp("-s", argv[1]) == 0) || (strcmp("--search", argv[1]) == 0))
        {
            QString mediaTitle = getMediaTitle(a.arguments());
            apiManager.queryRequest(mediaTitle, ApiRequestManager::search);
        }
        else if ((strcmp("-t", argv[1]) == 0) || (strcmp("--type", argv[1]) == 0))
        {
            QString mediaTitle = getMediaTitle(a.arguments());
            apiManager.queryRequest(mediaTitle, ApiRequestManager::type);
        }
        else
        {
            qDebug() << "\nUnrecognized parameter. Correct usage:";
            showMenu();
        }
    }
    else
    {
        qDebug() << "\nUsage:";
        showMenu();
    }

    return 0;
}

