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
    Article a(1212,"titre de l'article","texte de l'article");
    std::cout << TextExport().exportNote(&a).toStdString() << std::endl;
    Document d(1314,"Document hyper important");
    d.addSubNote(&a);
    std::cout << TextExport().exportNote(&d).toStdString() << std::endl;

    return app.exec();
}
