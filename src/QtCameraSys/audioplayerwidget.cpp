#include "audioplayerwidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTime>


AudioPlayerWidget::AudioPlayerWidget(QWidget *parent)
    : QWidget(parent),
      m_playButton(nullptr),
      m_forwardToolButton(nullptr),
      m_backwardToolButton(nullptr),
      m_openfileButton(nullptr),
      m_positionSlider(nullptr),
      m_positionLabel(nullptr),
      m_infoLabel(nullptr)
{
    initUI();
}

void AudioPlayerWidget::initUI()
{
    m_playButton = new QPushButton("Play",this);
    m_playButton->setToolTip(tr("Play"));

    m_backwardToolButton =new QPushButton("<<",this);
    m_backwardToolButton->setToolTip(tr("Back"));

    m_forwardToolButton =new QPushButton(">>",this);
    m_forwardToolButton->setToolTip(tr("next"));

    m_openfileButton = new QPushButton("Open",this);
    m_openfileButton->setToolTip(tr("Open a file..."));
    m_openfileButton->setFixedSize(m_playButton->sizeHint());

    m_positionSlider = new QSlider(Qt::Horizontal, this);
    m_positionSlider->setEnabled(false);
    m_positionSlider->setToolTip(tr("Seek"));

    m_infoLabel = new QLabel(this);
    m_positionLabel = new QLabel(tr("00:00"), this);
    m_positionLabel->setMinimumWidth(m_positionLabel->sizeHint().width());

    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(m_openfileButton);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_backwardToolButton);
    controlLayout->addWidget(m_forwardToolButton);

    QHBoxLayout *sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(m_positionSlider);
    sliderLayout->addWidget(m_positionLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_infoLabel);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(controlLayout);
    mainLayout->addStretch();

    connect(m_playButton,SIGNAL(clicked(bool)), this, SLOT(togglePlayback()));
    connect(m_backwardToolButton,SIGNAL(clicked(bool)),this,SLOT(seekBackward()));
    connect(m_forwardToolButton,SIGNAL(clicked(bool)),this,SLOT(seekForward()));
    connect(m_openfileButton,SIGNAL(clicked(bool)), this, SLOT(openFile()));
    connect(m_positionSlider, SIGNAL(valueChanged(int)), this, SLOT(setPosition(int)));

    connect(&m_mediaPlayer, &QMediaPlayer::positionChanged, this, &AudioPlayerWidget::updatePosition);
    connect(&m_mediaPlayer, &QMediaPlayer::durationChanged, this, &AudioPlayerWidget::updateDuration);
    connect(&m_mediaPlayer, &QMediaObject::metaDataAvailableChanged, this, &AudioPlayerWidget::updateInfo);
    connect(&m_mediaPlayer,&QMediaPlayer::stateChanged,this,&AudioPlayerWidget::updateState);
}

void AudioPlayerWidget::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath =
            QFileDialog::getOpenFileName(this, tr("Open File"),
                                         musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                         tr("MP3 files (*.mp3);;All files (*.*)"));
    if (!filePath.isEmpty())
        playFile(filePath);
}

void AudioPlayerWidget::playFile(const QString &filePath)
{
    m_playButton->setEnabled(true);
    m_infoLabel->setText(QFileInfo(filePath).fileName());

    m_mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
    m_mediaPlayer.play();
    emit postMessage("Audio is playing...");
}

void AudioPlayerWidget::togglePlayback()
{
    if (m_mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
    {
        openFile();
    }
    else if (m_mediaPlayer.state() == QMediaPlayer::PlayingState)
    {
        m_mediaPlayer.pause();
        emit postMessage("pause");
    }
    else
    {
        m_mediaPlayer.play();
        emit postMessage("Audio is playing...");
    }

}

void AudioPlayerWidget::seekForward()
{
    m_positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void AudioPlayerWidget::seekBackward()
{
    m_positionSlider->triggerAction(QSlider::SliderPageStepSub);
}

void AudioPlayerWidget::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        m_playButton->setToolTip(tr("Pause"));
        m_playButton->setText(tr("Pause"));
    }
    else
    {
        m_playButton->setToolTip(tr("Play"));
        m_playButton->setText(tr("Play"));
    }
}

void AudioPlayerWidget::updatePosition(qint64 position)
{
    m_positionSlider->setValue(position);
    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    m_positionLabel->setText(duration.toString(tr("mm:ss")));
}

void AudioPlayerWidget::updateDuration(qint64 duration)
{
    m_positionSlider->setRange(0,duration);
    m_positionSlider->setEnabled(duration>0);
    m_positionSlider->setPageStep(duration/10);
}

void AudioPlayerWidget::setPosition(int position)
{
    if (qAbs(m_mediaPlayer.position() - position) > 99)
        m_mediaPlayer.setPosition(position);
}

void AudioPlayerWidget::updateInfo()
{
    QStringList info;
    QString author = m_mediaPlayer.metaData("Author").toString();
    if (!author.isEmpty())
        info += author;
    QString title = m_mediaPlayer.metaData("Title").toString();
    if (!title.isEmpty())
        info += title;
    if (!info.isEmpty())
        m_infoLabel->setText(info.join(tr(" - ")));
}


