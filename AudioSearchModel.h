#ifndef AUDIOSEARCHMODEL_H
#define AUDIOSEARCHMODEL_H

#include "AudioInfo.h"

#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QObject>

class AudioSearchModel : public QAbstractListModel
{
    Q_OBJECT
public:

    Q_PROPERTY(bool isSearching READ isSearching NOTIFY isSearchingChanged FINAL)

    explicit AudioSearchModel(QObject *parent = nullptr);

    enum Role{
        AudioNameRole = Qt::UserRole + 1,
        AudioAuthorRole,
        AudioImageSourceRole,
        AudioSourceRole
    };


signals:

    void isSearchingChanged();

public slots:
    void searchSong(const QString &songName);
    void parseResponse();

private:
    QList<AudioInfo*> m_audioList;
    QNetworkAccessManager m_networkAcessManager;
    QNetworkReply* m_networkReply =  nullptr;

    // QAbstractItemModel interface
    bool m_isSearching;

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    bool isSearching() const;
    void setisSearching(bool newIsSearching);
};

#endif // AUDIOSEARCHMODEL_H
