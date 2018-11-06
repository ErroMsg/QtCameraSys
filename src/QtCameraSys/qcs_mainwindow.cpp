#include "qcs_mainwindow.h"
#include "ui_qcs_mainwindow.h"
#include "audioplayerwidget.h"
#include "cameradisplaywidget.h"
#include "videoplayerwidget.h"
#include <QTabWidget>
#include <QLabel>


QCS_MainWindow::QCS_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCS_MainWindow),
    m_pMessageLabel(nullptr),
    m_pCameraDisplayWidget(nullptr),
    m_pVideoPlayerWidget(nullptr),
    m_pAudioPlayerWidget(nullptr)
{
    initUI();
    initStatusBar();
    initCenterWidget();
//    VideoCapture video;
//    Mat frame2;
//    video.open("/home/gaopy/testData/test.avi");
//    while (video.isOpened())
//    {
//        video >> frame2;
//        imshow("video", frame2);
//        if (cvWaitKey(40) == 27) //cvWaitKey的参数相当于多少ms一帧，现在是40ms一帧，1s25帧
//            break; //按ESC就退出
//    }

/*
    Mat input_image;
    VideoCapture cam(0);
    if (!cam.isOpened())
        exit(0);

    VideoWriter write;
    write.open("/home/gaopy/testData/test.avi",VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, Size(640, 480), true);

    while (true)
    {
        cam >> input_image;
        imshow("VideoPlay", input_image);
        write.write(input_image);
        if (waitKey(30) == 27) break;

    }*/

}

QCS_MainWindow::~QCS_MainWindow()
{
    delete ui;
}

void QCS_MainWindow::initUI()
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->menuBar->hide();

}

void QCS_MainWindow::initStatusBar()
{
    m_pMessageLabel = new QLabel("msg:cc");
    ui->statusBar->addPermanentWidget(m_pMessageLabel);
}

void QCS_MainWindow::initCenterWidget()
{
    QTabWidget *tw = new QTabWidget(this);

    m_pCameraDisplayWidget = new CameraDisplayWidget();
    m_pVideoPlayerWidget = new VideoPlayerWidget();
    m_pAudioPlayerWidget = new AudioPlayerWidget();

    tw->addTab(m_pCameraDisplayWidget,"CameraDisplay");
    tw->addTab(m_pVideoPlayerWidget,"VideoPlayer");
    tw->addTab(m_pAudioPlayerWidget,"AudioPlayer");
    this->setCentralWidget(tw);
}

void QCS_MainWindow::updateMessage(QString str)
{
    m_pMessageLabel->setText(str);
}


