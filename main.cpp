#include "mainwindow.h"

#include <QApplication>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QImage>

int main(int argc, char *argv[])
{
    const auto name = QObject::tr("Icon Chopper");

    QApplication a(argc, argv);
    a.setApplicationName(name);

    MainWindow w;
    w.setWindowTitle(name);
    w.show();
    return a.exec();
}
