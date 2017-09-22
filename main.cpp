#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <gsl/config.h>
#include <gsl/gsl_sf_bessel.h>
#include "datatypes.h"

void environTest()
{
    double x =5.0;
    double y =gsl_sf_bessel_J0(x);
    qDebug()<< "J0("<< x <<") = " << y<< endl;
    qDebug()<<sizeof(float32)<<endl;
    qDebug()<<sizeof(int32_t)<<endl;
    qDebug()<<sizeof(float64)<<endl;
    qDebug()<<sizeof(int64_t)<<endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    environTest();

    MainWindow w;
    w.show();

    return a.exec();
}

