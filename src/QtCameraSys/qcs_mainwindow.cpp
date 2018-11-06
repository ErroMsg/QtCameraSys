#include "qcs_mainwindow.h"
#include "ui_qcs_mainwindow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;


QCS_MainWindow::QCS_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCS_MainWindow)
{
    ui->setupUi(this);
    Mat input_image;
    VideoCapture cam(0);
    if (!cam.isOpened())
        exit(0);
    namedWindow("摄像头");
    while (true)
    {
        cam >> input_image;
        imshow("input image", input_image);
        if (27 == waitKey(30)) break;
    }

}

QCS_MainWindow::~QCS_MainWindow()
{
    delete ui;
}
