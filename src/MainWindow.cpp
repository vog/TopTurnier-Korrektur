// Copyright (C) Volker Diels-Grabsch <v@njh.eu>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tableModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(tableModel);
    tableModel->setHorizontalHeaderItem(0, new QStandardItem());
    tableModel->setHorizontalHeaderItem(1, new QStandardItem());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFileStatus(const QFile &file, const QString &status)
{
    QList<QStandardItem *> items;
    items.append(new QStandardItem(status));
    items.append(new QStandardItem(file.fileName()));
    tableModel->insertRow(0, items);
}

void MainWindow::setFinished()
{
    QMap<QString, int> counts;
    for (int row = 0; row < tableModel->rowCount(); row++) {
        const QString status = tableModel->item(row, 0)->text();
        if (!counts.contains(status)) counts[status] = 0;
        counts[status] = counts[status] + 1;
    }
    QStringList countTexts;
    foreach (QString status, counts.keys()) {
        countTexts.append(QString("%1 %2").arg(counts[status]).arg(status));
    }
    const QString origLabelText = ui->label->text();
    ui->label->setText(QString("%1: %2").arg(origLabelText).arg(countTexts.join(", ")));
    ui->quitButton->setEnabled(true);
}

void MainWindow::setAborted()
{
    ui->tableView->setTextElideMode(Qt::ElideRight);
    QList<QStandardItem *> items;
    items.append(new QStandardItem("Fehler"));
    items.append(new QStandardItem("Bitte das zu korrigierende Export-Verzeichnis auf das Programm-Symbol ziehen"));
    tableModel->insertRow(0, items);
    ui->quitButton->setEnabled(true);
}
