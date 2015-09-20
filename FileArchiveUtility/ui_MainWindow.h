/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Sun Sep 20 21:45:49 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *fileLocation;
    QPushButton *selectFileButton;
    QLabel *label_2;
    QTableView *tableView;
    QPushButton *saveCurrent;
    QPushButton *retrieveVersion;
    QPushButton *setReference;
    QPushButton *showComment;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 31, 16));
        fileLocation = new QLineEdit(centralwidget);
        fileLocation->setObjectName(QString::fromUtf8("fileLocation"));
        fileLocation->setEnabled(false);
        fileLocation->setGeometry(QRect(80, 30, 451, 27));
        selectFileButton = new QPushButton(centralwidget);
        selectFileButton->setObjectName(QString::fromUtf8("selectFileButton"));
        selectFileButton->setGeometry(QRect(550, 30, 85, 27));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 171, 31));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(40, 130, 491, 371));
        saveCurrent = new QPushButton(centralwidget);
        saveCurrent->setObjectName(QString::fromUtf8("saveCurrent"));
        saveCurrent->setEnabled(false);
        saveCurrent->setGeometry(QRect(550, 130, 131, 27));
        retrieveVersion = new QPushButton(centralwidget);
        retrieveVersion->setObjectName(QString::fromUtf8("retrieveVersion"));
        retrieveVersion->setEnabled(false);
        retrieveVersion->setGeometry(QRect(550, 170, 131, 27));
        setReference = new QPushButton(centralwidget);
        setReference->setObjectName(QString::fromUtf8("setReference"));
        setReference->setEnabled(false);
        setReference->setGeometry(QRect(550, 210, 131, 27));
        showComment = new QPushButton(centralwidget);
        showComment->setObjectName(QString::fromUtf8("showComment"));
        showComment->setEnabled(false);
        showComment->setGeometry(QRect(550, 250, 131, 27));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        selectFileButton->setText(QApplication::translate("MainWindow", "Select File", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Version Data</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        saveCurrent->setText(QApplication::translate("MainWindow", "Save Current", 0, QApplication::UnicodeUTF8));
        retrieveVersion->setText(QApplication::translate("MainWindow", "Retrieve Version", 0, QApplication::UnicodeUTF8));
        setReference->setText(QApplication::translate("MainWindow", "Set as reference", 0, QApplication::UnicodeUTF8));
        showComment->setText(QApplication::translate("MainWindow", "Show comment", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
