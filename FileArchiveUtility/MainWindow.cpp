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

void MainWindow::selectFile() {
    
}

void MainWindow::retrieveVersionData() {
    
}

void MainWindow::createFirstVersion() {
    
}

void MainWindow::saveCurrent() {
    
}

void MainWindow::selectEntry() {
    
}

bool MainWindow::showComment() {
    
}

bool MainWindow::retrieveVersion() {
    
}

void MainWindow::setReferenceVersion() {
    
}
        
MainWindow::~MainWindow() {
}

void MainWindow::selectFile(){
    
    //Use standard QtFileDialog allowing user to enter filename
    //Display name of file as chosen by user
    //Invoke FileArchiver::exists()
    //If true
        //Invoke retrieveVersionDataForFile()
    //Else
        //createFirstVersion())
    
}

void MainWindow::retrieveVersionData(){
    
    //Clear data in table used to display version database 
    //invoke getVersionInfo(filename)
    //Populate table
    //Adjust display
    
};



void MainWindow::createFirstVersion(){
    
    //Dialog to get comment 
    
    //insertNew()
    
    //retrieveVersionDataForFile()
    
};
void MainWindow::saveCurrent(){
 
    
    //differs(filename)
    //if true
        //cout << "Same file! << endl; return;
    //else
        //get comment
    //update(filename,comment)
    //retrieveVersionDataForFile()
}

void MainWindow::selectEntry(){
    //
    
    
};
bool MainWindow::showComment(){
    
    //getComment(filename,verNum);
    //display Qt "Information Dialog"
    
};
bool MainWindow::retrieveVersion(){
    
    //retrieveForm
    //retrieveVersion())
    
};
void MainWindow::setReferenceVersion(){
    
    //Qt confirmation dialog 
    
    //if yes
        //getComment()
        //setReference(filename,verNum,comment)
    //retrieveVersionDataForFile()
    
};
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
