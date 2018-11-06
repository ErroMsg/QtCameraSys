#include "cameradisplaywidget.h"
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>

CameraDisplayWidget::CameraDisplayWidget(QWidget *parent) : QWidget(parent)
    ,m_pDisplayLabel(nullptr)
{
    QPushButton *pOpenBt = new QPushButton("Open Camera");
    QPushButton *pCloseBt = new QPushButton("Close Camera");
    QPushButton *pSaveBt = new QPushButton("Save Video");
    QPushButton *pReplayBt = new QPushButton("Replay Video");

    QHBoxLayout *hlyt = new QHBoxLayout;
    hlyt->addWidget(pOpenBt);
    hlyt->addWidget(pCloseBt);
    hlyt->addWidget(pSaveBt);
    hlyt->addWidget(pReplayBt);

    m_pDisplayLabel = new QLabel();
    m_pDisplayLabel->setMinimumSize(800,600);

    QVBoxLayout *pvlt = new QVBoxLayout();
    pvlt->addWidget(m_pDisplayLabel);
    pvlt->addLayout(hlyt);

    this->setLayout(pvlt);
    restoreDisplayer();
}

void CameraDisplayWidget::restoreDisplayer()
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    m_pDisplayLabel->setAutoFillBackground(true);
    m_pDisplayLabel->setPalette(palette);
}
