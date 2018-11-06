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
