#include "cameradisplaywidget.h"
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <QImage>
#include <QFileDialog>
#include <QDebug>
#include <QTime>


CameraDisplayWidget::CameraDisplayWidget(QWidget *parent) : QWidget(parent)
  ,m_pDisplayLabel(nullptr),
    m_status(PlayStatus::STOP),
    m_type(PlayType::NONE),
    m_timer(nullptr),
    m_bsavefile(false)
{
    initUI();
}

CameraDisplayWidget::~CameraDisplayWidget()
{
    closeCamera();
}

void CameraDisplayWidget::playFile(QString filePath)
{
    if(m_cam.open(filePath.toStdString()))
    {
        m_timer->start(50);
        updatePlayStatus(PlayStatus::RUNNING,PlayType::REPLAY);
        emit postMessage(QString("Replay file open success"));

    }
    else
    {
        updatePlayStatus(PlayStatus::STOP,PlayType::NONE);
        emit postMessage(QString("Replay file open failed！"));
    }
}

void CameraDisplayWidget::beginOrStopSave()
{
    if(m_type != PlayType::CAMERA)
    {
        emit postMessage("Current status can not save video!");
        return;
    }

    if(m_status == PlayStatus::RUNNING)
    {
        if(!m_bsavefile)
        {
            //save path can be config by .ini file or setup window.
            QString filename = "./VideoData" + QTime::currentTime().toString() + ".avi";
            if(!filename.isEmpty())
            {
                saveFile(filename);
                emit postMessage("Saving file...");
            }
        }
        else
        {
            qDebug()<<"stop savefile";
            m_bsavefile = false;
            m_writer.release();
            emit postMessage("Stop save file!");
        }
    }
    else
    {
        emit postMessage("Please open camera to save file");
        return;
    }
}

void CameraDisplayWidget::saveFile(QString savefilePath)
{
    if(m_writer.open(savefilePath.toStdString(),VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(640, 480), true))
    {
        qDebug()<<"m_writer.open:" << savefilePath;
        m_bsavefile = true;
    }
    else
    {
        emit postMessage("File save path is invalid!");
        return;
    }
}

void CameraDisplayWidget::openCamera()
{
    //current use 0 index of camera,this can be set by Interface!
    if(m_cam.open(0))
    {
        m_timer->start(50);
        updatePlayStatus(PlayStatus::RUNNING,PlayType::CAMERA);
        emit postMessage(QString("camera open success"));

    }
    else
    {
        updatePlayStatus(PlayStatus::STOP,PlayType::NONE);
        emit postMessage(QString("camera open failed！"));
    }
}

void CameraDisplayWidget::closeCamera()
{
    m_bsavefile = false;
    updatePlayStatus(PlayStatus::STOP,PlayType::NONE);

    m_timer->stop();
    m_cam.release();
    m_writer.release();
    m_pDisplayLabel->clear();//clear the last picture
    emit postMessage(QString("Camera closed!"));
}

void CameraDisplayWidget::displayFrame()
{
    m_cam >> m_frame;

    if(m_bsavefile)
    {
        m_writer.write(m_frame);
    }

    QImage img = QImage((const unsigned char*)m_frame.data, m_frame.cols, m_frame.rows, QImage::Format_RGB888).rgbSwapped();
    m_pDisplayLabel->setPixmap(QPixmap::fromImage(img));

}

void CameraDisplayWidget::replayFile()
{
    if(m_status != PlayStatus::STOP)
        closeCamera();

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open video"),".",tr("video File(*.avi)"));
    playFile(fileName);

    updatePlayStatus(PlayStatus::RUNNING,PlayType::REPLAY);
}

void CameraDisplayWidget::updatePlayStatus(PlayStatus status, PlayType type)
{
    m_status = status;
    m_type = type;
}

void CameraDisplayWidget::initUI()
{
    QPushButton *pOpenBt = new QPushButton("Open Camera");
    QPushButton *pCloseBt = new QPushButton("Close Camera");
    QPushButton *pSaveBt = new QPushButton("Begin/Stop Save");
    QPushButton *pReplayBt = new QPushButton("Replay Video");

    QHBoxLayout *hlyt = new QHBoxLayout;
    hlyt->addWidget(pOpenBt);
    hlyt->addWidget(pCloseBt);
    hlyt->addWidget(pSaveBt);
    hlyt->addWidget(pReplayBt);

    m_pDisplayLabel = new QLabel();
    //m_pDisplayLabel->setMinimumSize(800,600);

    QVBoxLayout *pvlt = new QVBoxLayout();
    pvlt->addWidget(m_pDisplayLabel);
    pvlt->addLayout(hlyt);

    this->setLayout(pvlt);

    //label fill black
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    m_pDisplayLabel->setAutoFillBackground(true);
    m_pDisplayLabel->setPalette(palette);

    m_timer = new QTimer(this);
    connect(pOpenBt,SIGNAL(clicked(bool)),this,SLOT(openCamera()));
    connect(pSaveBt,SIGNAL(clicked(bool)),this,SLOT(beginOrStopSave()));
    connect(pCloseBt,SIGNAL(clicked(bool)),this,SLOT(closeCamera()));
    connect(pReplayBt,SIGNAL(clicked(bool)),this,SLOT(replayFile()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(displayFrame()));
}

