// Copyright (C) Volker Diels-Grabsch <v@njh.eu>

#include "FixFiles.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    if (argc == 2) {
        const QDir dir(argv[1]);
        fixFiles(dir, mainWindow);
        mainWindow.setFinished();
    } else {
        mainWindow.setAborted();
    }
    return a.exec();
}
