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

Article a(1212,"titre de l'article 1","texte de l'article 1\nDeuxiéme ligne!");
Article b(1222,"titre de l'article 2","texte de l'article 2");
Image c(5623,"Image 1","description 1","http://www.canevas.com/I-Grande-123873-bouquet-de-tulipes.net.jpg");
Video e(5623,"Video 1","description 1","http://example.fr/video1.mpg");
Audio f(5623,"Audio 1","description 1","http://example.fr/fichier.mp3");
Document d(1314,"Document hyper important");
Document d2(13314,"Document moins important");


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Notes Manager");
    NotesManager* nm = NotesManager::getInstance();
    nm->setPath("../notesmanager/workplace");
    nm->load();
    for(NotesManager::Iterator it = nm->begin();it != nm->end();++it){
        qDebug() << (*it)->getId() << (*it)->getTitle();
    }
    SaveTextExport().save();
    MainWindow* m = MainWindow::getInstance();
    m->show();
    return app.exec();
}
