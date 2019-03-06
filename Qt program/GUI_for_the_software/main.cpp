#include "mainwindow.h"
#include "dropletidpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //DropletIdPage w;
    w.show();

    return a.exec();
}
