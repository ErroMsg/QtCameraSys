#ifndef CAMERADISPLAYWIDGET_H
#define CAMERADISPLAYWIDGET_H

#include <QWidget>
#include "opencvinclude.h"
class QTimer;
class QLabel;

enum class PlayStatus
{
    STOP = 0,
    RUNNING
};

enum class PlayType
{
    NONE = 0,
    CAMERA,
    REPLAY
};

class CameraDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraDisplayWidget(QWidget *parent = nullptr);
    ~CameraDisplayWidget();

public slots:
    void beginOrStopSave();
    void openCamera();
    void closeCamera();
    void displayFrame();
    void replayFile();

signals:
    void postMessage(QString);

private:
    void initUI();
    void saveFile(QString savefilePath);
    void playFile(QString filePath);
    void updatePlayStatus(PlayStatus status,PlayType type);
private:
    QLabel *m_pDisplayLabel;
    Mat m_frame;
    QTimer *m_timer;
    VideoCapture m_cam;
    VideoWriter m_writer;
    bool m_bsavefile;

    PlayStatus m_status;
    PlayType m_type;

};

#endif // CAMERADISPLAYWIDGET_H
