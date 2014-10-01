#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/image/image/icon.png"));//设置图标
    w.showFirstNote();

    return a.exec();
}
