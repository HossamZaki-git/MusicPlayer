#include "AudioSearchModel.h"
#include "AudioInfo.h"
#include <QJsonDocument>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>

namespace {
const QString & mainURL = "https://api.jamendo.com/v3.0/tracks/";
const QString & clientId = "85b6a59c";
}

AudioSearchModel::AudioSearchModel(QObject *parent)
    : QAbstractListModel{parent}
{}

void AudioSearchModel::searchSong(const QString &songName)
{
    if(songName.trimmed().isEmpty())
        return;
    if(m_networkReply)
    {
        // aborts any network connection that is still opened
        m_networkReply -> abort();
        // delete after the end of any dependency on it
        m_networkReply -> deleteLater();
        m_networkReply = nullptr;
    }

    setisSearching(true);

    QUrlQuery queryString;
    queryString.addQueryItem("client_id", clientId);
    queryString.addQueryItem("namesearch", songName);
    queryString.addQueryItem("format", "json");

    m_networkReply = m_networkAcessManager.get(QNetworkRequest(mainURL + "?" + queryString.toString()));
    // This signal slot will not be duplicated every time a request is made because:
    // m_networkReply will carry a new instance with every request and the old one will be destroyed with all its signal-slot connection
    connect(m_networkReply, &QNetworkReply::finished, this, &AudioSearchModel::parseResponse);
}

void AudioSearchModel::parseResponse()
{
    // The request failed
    if(m_networkReply-> error() != QNetworkReply::NoError)
    {
        qCritical() << "Error in the response: "<< m_networkReply -> errorString();
        setisSearching(false);
        return;
    }

    QByteArray allInBytes = m_networkReply-> readAll();
    QJsonDocument allInJSON = QJsonDocument::fromJson(allInBytes);
    QJsonObject headers = allInJSON["headers"].toObject();

    // The request reached the server but the server didn't give a successful response
    if(headers["status"].toString() != "success")
    {
        qWarning() << "A non-success status from the headers: " << headers["error_string"];
        setisSearching(false);
        return;
    }

    beginResetModel();

    qDeleteAll(m_audioList);
    m_audioList.clear();

    AudioInfo *audioInfo;
    QJsonArray results = allInJSON["results"].toArray();
    for(const auto &result : results)
    {
        QJsonObject entry = result.toObject();

         if (!entry["audiodownload_allowed"].toBool())
            continue;

         audioInfo = new AudioInfo(this);

         audioInfo->setTitle(entry["name"].toString());
         audioInfo->setAuthorName(entry["artist_name"].toString());
         audioInfo->setImageSource(entry["image"].toString());
         audioInfo->setAudioSource(entry["audiodownload"].toString());

         m_audioList << audioInfo;
    }

    endResetModel();

    m_networkReply -> deleteLater();
    m_networkReply = nullptr;
    setisSearching(false);
}

int AudioSearchModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.length();
}

QVariant AudioSearchModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() < m_audioList.length())
    {
        AudioInfo* instance = m_audioList[index.row()];

        switch((Role)role)
        {
        case AudioNameRole:
            return instance -> title();
        case AudioAuthorRole:
            return instance -> authorName();
        case AudioImageSourceRole:
            return instance -> imageSource();
        case AudioSourceRole:
            return instance -> audioSource();
        }
    }
    return {};
}

QHash<int, QByteArray> AudioSearchModel::roleNames() const
{
    QHash<int,QByteArray> nameOfRole;

    nameOfRole[AudioNameRole] = "audioName";
    nameOfRole[AudioAuthorRole] = "audioAuthor";
    nameOfRole[AudioImageSourceRole] = "audioImageSource";
    nameOfRole[AudioSourceRole] = "audioSource";

    return nameOfRole;
}

bool AudioSearchModel::isSearching() const
{
    return m_isSearching;
}

void AudioSearchModel::setisSearching(bool newIsSearching)
{
    if (m_isSearching == newIsSearching)
        return;
    m_isSearching = newIsSearching;
    emit isSearchingChanged();
}
