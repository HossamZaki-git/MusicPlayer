#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QObject>
#include <qqml.h>
#include <QUrl>

class AudioInfo : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int songIndex READ songIndex WRITE setSongIndex NOTIFY songIndexChanged FINAL REQUIRED)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString authorName READ authorName WRITE setAuthorName NOTIFY authorNameChanged FINAL)
    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged FINAL)
    Q_PROPERTY(QUrl videoSource READ videoSource WRITE setVideoSource NOTIFY videoSourceChanged FINAL)
    Q_PROPERTY(QUrl audioSource READ audioSource WRITE setAudioSource NOTIFY audioSourceChanged FINAL REQUIRED)

public:
    explicit AudioInfo(QObject *parent = nullptr);

    int songIndex() const;
    void setSongIndex(int newSongIndex);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString authorName() const;
    void setAuthorName(const QString &newAuthorName);

    QUrl imageSource() const;
    void setImageSource(const QUrl &newImageSource);

    QUrl videoSource() const;
    void setVideoSource(const QUrl &newVideoSource);

    QUrl audioSource() const;
    void setAudioSource(const QUrl &newAudioSource);

signals:
    void songIndexChanged();
    void titleChanged();

    void authorNameChanged();

    void imageSourceChanged();

    void videoSourceChanged();

    void audioSourceChanged();

private:
    int m_songIndex;
    QString m_title;
    QString m_authorName;
    QUrl m_imageSource;
    QUrl m_videoSource;
    QUrl m_audioSource;
};

#endif // AUDIOINFO_H
