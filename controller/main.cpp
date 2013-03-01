/*
 * File:   main.cpp
 * Author: petris
 *
 * Created on 19. listopad 2012, 14:51
 */

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "../view/MainWindow.h"
#include "../model/FilterRulesModel.h"
#include "../lib/Logger.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    MainWindow main;
    
    Logger::getInstance()->clearLog();
    
    if(getuid() != 0)
    {
        QMessageBox::warning(NULL, QString::fromUtf8("Aditionals privileges needed"),
                QString::fromUtf8("It`s recommended to run application with root privileges."),
                QMessageBox::Ok, QMessageBox::Ok);
    }
    
    FilterRulesModel *rulesModel = new FilterRulesModel();
    main.setRulesViewModel(rulesModel);
    
    main.show();
    
    return app.exec();
}
