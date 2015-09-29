/*
 * File:   main.cpp
 * Author: myww749
 *
 * Created on 5 September 2015, 9:30 PM
 */

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    MainWindow window;
    window.show();

    return app.exec();
}
