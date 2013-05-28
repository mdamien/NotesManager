#include <QApplication>
#include <QPushButton>
#include <QDebug>

#include <iostream>
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "mainwindow.h"
#include "notesmanager.h"
#include "textexport.h"
#include "htmlexport.h"
#include "savetextexport.h"
#include "tagmanager.h"
#include "notesparser.h"
#include "settingsdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Notes Manager");
    NotesManager* nm = NotesManager::getInstance();
    nm->load(SettingsDialog::workplace());
    for(NotesManager::Iterator it = nm->begin();it != nm->end();++it){
        qDebug() << (*it)->getId() << (*it)->getTitle();
    }
    MainWindow* m = MainWindow::getInstance();
    m->show();
    /*SettingsDialog s;
    s.show();*/
    return app.exec();
}
