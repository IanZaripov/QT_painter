#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    lineWidget w;
    w.show();
    return a.exec();
}
