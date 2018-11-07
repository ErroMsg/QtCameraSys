#include "qcs_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCS_MainWindow w;
    w.show();

    return a.exec();
}
