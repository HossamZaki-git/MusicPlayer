#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <AudioInfo.h>
#include <QAbstractListModel>
#include <QMediaPlayer>
#include <QObject>

class PlayerController : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged FINAL)
    Q_PROPERTY(AudioInfo* currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged FINAL)

public:

    // The given names of data insdie each record of the internal sequence
    enum Role{
        // Qt::UserRole = 256 which is the start of the allowed numbers for user custom roles
        // because roles numbers can't match accross the application
        AudioTitileRole = Qt::UserRole + 1,
        AudioAuthorNameRole,
        AudioSourceRole,
        AudioImageSourceRole,
        AudioVideoSourceRole
    };

    explicit PlayerController(QObject *parent = nullptr);


    bool isPlaying() const;

    Q_INVOKABLE void next();

public slots:
    void togglePlayButton();
    void previous();
    void changeAudioSource(const QUrl &audioSource);
    void addAudio(const QString& title,
                  const QString& authorName,
                  const QUrl& audioSource,
                  const QUrl& imageSource,
                  const QUrl& videoSource = QUrl());
    void removeAudio(int index);

signals:
    void isPlayingChanged();

    void currentSongChanged();

private:
    bool m_isPlaying = false;
    QMediaPlayer m_mediaPlayer;
    // The collection that will carry the data of the view internally
    QList<AudioInfo*> m_audioList;

    // QAbstractItemModel interface
    AudioInfo *m_currentSong = nullptr;

public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    AudioInfo *currentSong() const;
    void setCurrentSong(AudioInfo *newCurrentSong);
    void switchToAudioByIndex(int index);
};

#endif // PLAYERCONTROLLER_H
