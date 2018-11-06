#ifndef QCS_MAINWINDOW_H
#define QCS_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QCS_MainWindow;
}
class QLabel;
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

    QWidget *m_pCameraDisplayWidget;
    QWidget *m_pVideoPlayerWidget;
    QWidget *m_pAudioPlayerWidget;

};

#endif // QCS_MAINWINDOW_H
