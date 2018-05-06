// Copyright (C) Volker Diels-Grabsch <v@njh.eu>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void setFileStatus(const QFile &file, const QString &status);
    void setFinished();
    void setAborted();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *tableModel;
};

#endif // MAINWINDOW_H
