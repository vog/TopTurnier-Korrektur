# Copyright (C) Volker Diels-Grabsch <v@njh.eu>

DEFINES += QT_DEPRECATED_WARNINGS
FORMS += MainWindow.ui
HEADERS += FixFiles.h
HEADERS += MainWindow.h
QT = core gui widgets
SOURCES += FixFiles.cpp
SOURCES += MainWindow.cpp
SOURCES += main.cpp
TARGET = TopTurnier-Korrektur
TEMPLATE = app
