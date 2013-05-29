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
#include "historymanager.h"

void printNM()
{
    NotesManager* nm = NotesManager::getInstance();
    for(NotesManager::Iterator it = nm->begin();it != nm->end();++it){
        qDebug() << (*it)->getId() << (*it)->getTitle();
    }
}

int testHistory(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Notes Manager");
    NotesManager* nm = NotesManager::getInstance();
    nm->load(SettingsDialog::workplace());
    printNM();
    HistoryManager hm;
    qDebug("op 1");
    ModifyNoteTitle op1(nm->getNoteByID(1),"NEW TITLE");
    hm.addAndExec(&op1);
    printNM();
    qDebug("undo");
    hm.undo();
    printNM();
    return 0;
}

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
    app.exec();
}
