#include <QApplication>
#include <QPushButton>

#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindow FenetrePrincipale;
    FenetrePrincipale.show();

    return app.exec();
}
