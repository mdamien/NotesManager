#include <QApplication>
#include <QPushButton>

#include <iostream>

#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "mainwindow.h"
#include "notesmanager.h"

#include "textexport.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Article a(1212,"titre de l'article 1","texte de l'article 1");
    Article b(1222,"titre de l'article 2","texte de l'article 2");
    Image c(5623,"Image 1","description 1","http://example.fr/image1.jpg");
    Video e(5623,"Video 1","description 1","http://example.fr/video1.mpg");
    Audio f(5623,"Audio 1","description 1","http://example.fr/fichier.mp3");
    Document d(1314,"Document hyper important");
    d.addSubNote(&a);
    d.addSubNote(&b);
    d.addSubNote(&c);
    d.addSubNote(&e);
    d.addSubNote(&f);
    std::cout << TextExport().exportNote(&d).toStdString() << std::endl;
    std::cout << d.exportNote(new TextExport()).toStdString() << std::endl;
    return 0;//app.exec();
}
