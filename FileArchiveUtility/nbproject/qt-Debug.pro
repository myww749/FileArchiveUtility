# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-MacOSX
TARGET = FileArchiveUtility
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += FileArchiver.cpp FileRec.cpp MainWindow.cpp main.cpp
HEADERS += FileArchiver.h FileRec.h MainWindow.h constants.h ui_MainWindow.h
FORMS += MainWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-MacOSX
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/local/opt/sqlite/include/sqlite3.h 
LIBS += -lsqlite3.0 -lsqlite3 -lsqlite3  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
