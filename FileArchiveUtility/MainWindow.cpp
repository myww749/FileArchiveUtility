/*
 * File:   MainWindow.cpp
 * Author: myww749
 *
 * Created on 5 September 2015, 9:31 PM
 */

#include "MainWindow.h"

MainWindow::MainWindow() {
    widget.setupUi(this);
    
    
    
    connect(widget.idList, SIGNAL(clicked(const QModelIndex&)), this,
            SLOT(showSelection(const QModelIndex&)));
    connect(widget.printButton, SIGNAL(clicked()), this,
            SLOT(printSelectedRecord()));
    connect(widget.addRoleButton, SIGNAL(clicked()), this,
            SLOT(addRole()));
    connect(widget.removeRoleButton, SIGNAL(clicked()), this,
            SLOT(removeRole()));
}

MainWindow::~MainWindow() {
}

void MainWindow::selectFile();
void MainWindow::retrieveVersionData();
void MainWindow::createFirstVersion();
void MainWindow::saveCurrent();
void MainWindow::selectEntry();
bool MainWindow::showComment();
bool MainWindow::retrieveVersion();
void MainWindow::setReferenceVersion();