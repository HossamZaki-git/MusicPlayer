#include "PlayerController.h"
#include "QMediaDevices"
#include "QAudioDevice"
#include "QAudioOutput"

PlayerController::PlayerController(QObject *parent)
    : QAbstractListModel{parent}
{
    // Returns a list of the available audio devices
    const auto &audioOutputs = QMediaDevices::audioOutputs();
    if(!audioOutputs.isEmpty())
        //                            This object is responsible for taking the raw audio data from a file and sending it to the system's default speaker and its owned by m_mediaPlayer (when m_mediaPlayer is destroyed it will be destroyed too)
        m_mediaPlayer.setAudioOutput(new QAudioOutput(&m_mediaPlayer));

    addAudio(
        "Teach Me Tonight",
        "Frank Sinatra",
        QUrl("qrc:/qt/qml/MusicPlayer/assets/audio/TeachMeTonight.mpeg"),
        QUrl("qrc:/qt/qml/MusicPlayer/assets/images/song_1.jpg")
        );

    addAudio(
        "Fly Me to the Moon",
        "Frank Sinatra",
        QUrl("qrc:/qt/qml/MusicPlayer/assets/audio/FlyMeToTheMoon.mpeg"),
        QUrl("qrc:/qt/qml/MusicPlayer/assets/images/song_2.jpg")
        );

    addAudio(
        "Rolling in the Deep",
        "Adele",
        QUrl("qrc:/qt/qml/MusicPlayer/assets/audio/RollingInTheDeep.mpeg"),
        QUrl("qrc:/qt/qml/MusicPlayer/assets/images/song_3.jpg"),
        QUrl("qrc:/qt/qml/MusicPlayer/assets/videos/video_1.avi")
        );

    addAudio(
        "Set Fire To The Rain",
        "Adele",
        QUrl("qrc:/qt/qml/MusicPlayer/assets/audio/SetFireToTheRain.mp4"),
        QUrl("qrc:/qt/qml/MusicPlayer/assets/images/song_3.jpg")
        );

    setCurrentSong(m_audioList.first());
}

// tooglePlayButton --isPlayingChanged()-->
// setCurrentSong --currentSongChanged()-->

bool PlayerController::isPlaying() const
{
    return m_isPlaying;
}

void PlayerController::next()
{
    int index = m_audioList.indexOf(m_currentSong);
    index++;
    index %= m_audioList.length();
    setCurrentSong(m_audioList[index]);
}

void PlayerController::togglePlayButton()
{
    m_isPlaying = !m_isPlaying;
    emit isPlayingChanged();
    if(m_isPlaying)
        m_mediaPlayer.play();
    else
        m_mediaPlayer.pause();
}

void PlayerController::previous()
{
    int index = m_audioList.indexOf(m_currentSong);
    if(index == -1)
        index = 0;
    else
        index = !index ? m_audioList.length() - 1 : index - 1;
    setCurrentSong(m_audioList[index]);
}

void PlayerController::changeAudioSource(const QUrl &audioSource)
{
    m_mediaPlayer.stop();
    m_mediaPlayer.setSource(audioSource);
    if(m_isPlaying)
        m_mediaPlayer.play();
}

void PlayerController::addAudio(const QString &title, const QString &authorName, const QUrl &audioSource, const QUrl &imageSource, const QUrl &videoSource)
{
    //               the parent       first                  last                      first: the firsrt row before the insertion place           last: the last row after the insertion place
    beginInsertRows(QModelIndex(), m_audioList.length(), m_audioList.length());

    AudioInfo* audioInfo = new AudioInfo(this);

    audioInfo -> setTitle(title);
    audioInfo -> setAuthorName(authorName);
    audioInfo -> setAudioSource(audioSource);
    audioInfo -> setImageSource(imageSource);
    audioInfo -> setVideoSource(videoSource);

    m_audioList.append(audioInfo);

    endInsertRows();

}

void PlayerController::removeAudio(int index)
{
    if(index < 0 || index >= m_audioList.length())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    AudioInfo* targetRemove = m_audioList[index];

    if(targetRemove == m_currentSong)
    {
        if(m_audioList.length() > 1)
        {
            if(index)
                setCurrentSong(m_audioList[index - 1]);
            else
                setCurrentSong(m_audioList[index + 1]);
        }
        else
            setCurrentSong(nullptr);
    }

    m_audioList.removeAt(index);
    // will be deleted after all the processing depending on it finishes
    targetRemove -> deleteLater();
    endRemoveRows();
}

int PlayerController::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_audioList.length();
}

QVariant PlayerController::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() >= 0 && index.row() < m_audioList.length())
    {
        AudioInfo* audioInfo = m_audioList[index.row()];
        switch((Role) role)
        {
        case AudioAuthorNameRole:
            return audioInfo -> authorName();
        case AudioImageSourceRole:
            return audioInfo -> imageSource();
        case AudioSourceRole:
            return audioInfo -> audioSource();
        case AudioVideoSourceRole:
            return audioInfo -> videoSource();
        case AudioTitileRole:
            return audioInfo -> title();
        }
    }
    // in-valid QVariant
    return {};
}

QHash<int, QByteArray> PlayerController::roleNames() const
{
    QHash<int, QByteArray> names;

    //  The numbers (Roles)      The names used in QML files
    names[AudioAuthorNameRole] = "audioAuthorName";
    names[AudioTitileRole] = "audioTitle";
    names[AudioSourceRole] = "audioSource";
    names[AudioImageSourceRole] = "audioImageSource";
    names[AudioVideoSourceRole] = "audioVideoSource";

    return names;
}

AudioInfo *PlayerController::currentSong() const
{
    return m_currentSong;
}

void PlayerController::setCurrentSong(AudioInfo *newCurrentSong)
{
    if (m_currentSong == newCurrentSong)
        return;
    m_currentSong = newCurrentSong;
    emit currentSongChanged();

    // if ! nullptr
    if(m_currentSong)
        changeAudioSource(m_currentSong -> audioSource());
    else
    {
        m_mediaPlayer.stop();
        m_mediaPlayer.setSource(QUrl());
        m_isPlaying = false;
        emit isPlayingChanged();
    }
}

void PlayerController::switchToAudioByIndex(int index)
{
    if(index >= 0 && index < m_audioList.length())
        setCurrentSong(m_audioList[index]);
}
