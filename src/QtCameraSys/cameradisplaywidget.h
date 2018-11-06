#ifndef CAMERADISPLAYWIDGET_H
#define CAMERADISPLAYWIDGET_H

#include <QWidget>
#include "opencvinclude.h"
class QTimer;
class QLabel;
class CameraDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraDisplayWidget(QWidget *parent = nullptr);
private:
    void restoreDisplayer();
private:
    QLabel *m_pDisplayLabel;
    Mat m_frame;
    QTimer *timer;
    VideoCapture cam;
    VideoWriter write;
    bool bOpen;

};

#endif // CAMERADISPLAYWIDGET_H
