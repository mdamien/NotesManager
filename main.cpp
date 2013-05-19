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
    /*
    mainWindow FenetrePrincipale;
    FenetrePrincipale.show();
    */
    Article a(1212,"dsdds","sdsd");
    std::cout << TextExport().exportNote(&a).toStdString() << std::endl;

    return app.exec();
}
