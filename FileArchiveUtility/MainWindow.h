/* 
 * File:   MainWindow.h
 * Author: myww749
 *
 * Created on 5 September 2015, 9:31 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
    public slots:
        void selectFile();
        void retrieveVersionData();
        void createFirstVersion();
        void saveCurrent();
        void selectEntry();
        bool showComment();
        bool retrieveVersion();
        void setReferenceVersion();
private:
    Ui::MainWindow widget;
    FileArchiver file;
};

#endif	/* _MAINWINDOW_H */
