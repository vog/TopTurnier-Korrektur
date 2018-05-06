// Copyright (C) Volker Diels-Grabsch <v@njh.eu>

#include "FixFiles.h"
#include <QDirIterator>
#include <QRegularExpression>
#include <QTextStream>

static QString fixFileContent(const QString &content)
{
    QString newContent = content;
    newContent.replace(
        QString("<div class=\"erimgdiv\"><img src=\"endrunde.jpg\" width=600 class=\"erimg\"></div>"),
        QString("<!-- Removed \"erimgdiv\" -->"));
    newContent.replace(
        QString("$.get(\"endrunde.jpg\").done(function() { $(\".erimgdiv\").css(\"display\", \"block\"); }).fail(function() { $(\".erimgdiv\").css(\"display\", \"none\");});"),
        QString("// Removed \"erimgdiv\""));
    newContent.replace(
        QRegularExpression("<FRAME SRC=\"menu.htm\\?id=[0-9]+\">"),
        QString("<FRAME SRC=\"menu.htm\">"));
    return newContent;
}

static QString fixFile(QFile &file)
{
    const QString fileName = file.fileName();
    if (!fileName.endsWith(".htm") && !fileName.endsWith(".html")) {
        return "OK";
    }

    if (!file.open(QFile::ReadOnly)) {
        return "Lese-Fehler";
    }
    QTextStream inStream(&file);
    QString content = inStream.readAll();
    file.close();

    QString newContent = fixFileContent(content);
    if (content == newContent) {
        return "OK";
    }

    if (!file.open(QFile::WriteOnly)) {
        return "Schreib-Fehler";
    }
    QTextStream outStream(&file);
    outStream << newContent;
    outStream.flush();
    file.close();
    return "Korrigiert";
}

void fixFiles(const QDir &dir, MainWindow &mainWindow)
{
    const QString absPath = dir.absolutePath();
    QDirIterator dirIterator(absPath, QDir::Files, QDirIterator::Subdirectories);
    while (dirIterator.hasNext()) {
        QFile file(dirIterator.next());
        const QString status = fixFile(file);
        mainWindow.setFileStatus(file, status);
    }
}
