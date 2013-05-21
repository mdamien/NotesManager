#include <QApplication>
#include <QPushButton>

#include <iostream>

#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "mainwindow.h"
#include "notesmanager.h"
#include "articlefactory.h"
#include "textexport.h"
#include "htmlexport.h"

Article a(1212,"titre de l'article 1","texte de l'article 1");
Article b(1222,"titre de l'article 2","texte de l'article 2");
Image c(5623,"Image 1","description 1","http://www.canevas.com/I-Grande-123873-bouquet-de-tulipes.net.jpg");
Video e(5623,"Video 1","description 1","http://example.fr/video1.mpg");
Audio f(5623,"Audio 1","description 1","http://example.fr/fichier.mp3");
Document d(1314,"Document hyper important");
Document d2(13314,"Document moins important");

void testsMaxime()
{
    NotesManager& nm = *NotesManager::getInstance();
    nm.addRessource(&a);
    nm.addRessource(&b);
    nm.addRessource(&d);
    for(NotesManager::Iterator it = nm.begin(); it != nm.end(); ++it)
    {
        std::cout << TextExport().exportNote(*it).toStdString() << std::endl;
    }
}

void testsDamien()
{
    d.addSubNote(&c);
    d.addSubNote(&e);
    d.addSubNote(&f);
    d2.addSubNote(&a);
    d2.addSubNote(&c);
    d.addSubNote(&d2);

    //std::cout << TextExport().exportNote(&d).toStdString() << std::endl;
    std::cout << d.exportNote(new HTMLExport()).toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    d.addSubNote(&a);
    d.addSubNote(&b);
//    testsMaxime();
    ArticleFactory fact;
    Article* artou = (Article*) fact.buildNoteCopy(&a);
    std::cout << TextExport().exportNote(artou).toStdString() << std::endl;
    testsDamien();
    return 0;//app.exec();
}
