#ifndef QCS_MAINWINDOW_H
#define QCS_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QCS_MainWindow;
}
class QLabel;
class CameraDisplayWidget;
class AudioPlayerWidget;
class QCS_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QCS_MainWindow(QWidget *parent = 0);
    ~QCS_MainWindow();
public slots:
    void updateMessage(QString str);
private:
    void initUI();
    void initStatusBar();
    void initCenterWidget();
private:
    Ui::QCS_MainWindow *ui;

    QLabel *m_pMessageLabel;
    CameraDisplayWidget *m_pCameraDisplayWidget;
    AudioPlayerWidget *m_pAudioPlayerWidget;

};

#endif // QCS_MAINWINDOW_H
