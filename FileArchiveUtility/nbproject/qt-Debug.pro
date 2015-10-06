# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-MacOSX
TARGET = FileArchiveUtility
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets sql
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
DEFINES += DEBUG 
INCLUDEPATH += /usr/local/opt/sqlite/include/sqlite3.h /usr/local/Cellar/zlib/1.2.8/include/zlib.h /usr/local/Cellar/mysql/5.6.26/include 
LIBS += -lsqlite3.0 -lsqlite3 -lsqlite3 -lz -lmysqlclient  
