#ifndef AUDIOPLAYERWIDGET_H
#define AUDIOPLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>

class QPushButton;
class QSlider;
class QLabel;
class AudioPlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AudioPlayerWidget(QWidget *parent = nullptr);

public slots:
    void openFile();
    void playFile(const QString& filePath);
    void togglePlayback();
    void seekForward();
    void seekBackward();

private slots:
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateInfo();
signals:
    void postMessage(QString);

private:
    void initUI();

    QMediaPlayer m_mediaPlayer;
    QPushButton *m_playButton;
    QPushButton *m_forwardToolButton;
    QPushButton  *m_backwardToolButton;
    QPushButton *m_openfileButton;

    QSlider *m_positionSlider;
    QLabel *m_positionLabel;
    QLabel *m_infoLabel;

};

#endif // AUDIOPLAYERWIDGET_H
