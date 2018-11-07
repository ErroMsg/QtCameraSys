#include "qcs_mainwindow.h"
#include "ui_qcs_mainwindow.h"
#include "audioplayerwidget.h"
#include "cameradisplaywidget.h"
#include <QTabWidget>
#include <QLabel>


QCS_MainWindow::QCS_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCS_MainWindow),
    m_pMessageLabel(nullptr),
    m_pCameraDisplayWidget(nullptr),
    m_pAudioPlayerWidget(nullptr)
{
    initUI();
    initStatusBar();
    initCenterWidget();
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
    setWindowTitle("QtCameraSystem");
}

void QCS_MainWindow::initStatusBar()
{
    m_pMessageLabel = new QLabel(this);
    ui->statusBar->addPermanentWidget(m_pMessageLabel);
}

void QCS_MainWindow::initCenterWidget()
{
    QTabWidget *tw = new QTabWidget(this);

    m_pCameraDisplayWidget = new CameraDisplayWidget();
    m_pAudioPlayerWidget = new AudioPlayerWidget();

    tw->addTab(m_pCameraDisplayWidget,"Camera/VideoPlayer");
    tw->addTab(m_pAudioPlayerWidget,"AudioPlayer");
    this->setCentralWidget(tw);

    connect(m_pCameraDisplayWidget,SIGNAL(postMessage(QString)),this,SLOT(updateMessage(QString)));
    connect(m_pAudioPlayerWidget,SIGNAL(postMessage(QString)),this,SLOT(updateMessage(QString)));
}

void QCS_MainWindow::updateMessage(QString str)
{
    m_pMessageLabel->setText(str);
}


