# Copyright (C) Volker Diels-Grabsch <v@njh.eu>

SRCFILES += src/FixFiles.cpp
SRCFILES += src/FixFiles.h
SRCFILES += src/MainWindow.cpp
SRCFILES += src/MainWindow.h
SRCFILES += src/MainWindow.ui
SRCFILES += src/TopTurnier-Korrektur.pro
SRCFILES += src/main.cpp

.DELETE_ON_ERROR:

.PHONY: default
default: TopTurnier-Korrektur TopTurnier-Korrektur.zip

TopTurnier-Korrektur: $(SRCFILES)
	rm -rf _tmp_$@
	mkdir _tmp_$@
	cp $^ _tmp_$@
	cd _tmp_$@ && QT_SELECT=5 qmake
	cd _tmp_$@ && $(MAKE)
	mv _tmp_$@/$@ $@
	rm -rf _tmp_$@

TopTurnier-Korrektur.zip: $(SRCFILES)
	rm -rf _tmp_$@
	mkdir _tmp_$@
	cp $^ _tmp_$@
	cd _tmp_$@ && x86_64-w64-mingw32.static-qmake-qt5
	cd _tmp_$@ && $(MAKE) release
	cd _tmp_$@/release && upx TopTurnier-Korrektur.exe
	cd _tmp_$@/release && zip -9 $@ TopTurnier-Korrektur.exe
	mv _tmp_$@/release/$@ $@
	rm -rf _tmp_$@
