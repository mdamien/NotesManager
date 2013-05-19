#include "mainwindow.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
    sa = new QScrollArea(this);
    QFrame* container = new QFrame;
    vLayout = new QVBoxLayout(container);
    ArticleWidget* a1 = new ArticleWidget("titre1", "contenu1", this);
    ArticleWidget* a2 = new ArticleWidget("titre2", "contenu2", this);

    vLayout->addWidget(a1);
    vLayout->addWidget(a2);

    sa->setWidget(container);
    setCentralWidget(sa);

    //Ajout des menus :

    QMenu* menuFichier = menuBar()->addMenu("&Fichier");
    QAction* aNouveau = menuFichier->addAction("&Nouveau");
    connect(aNouveau, SIGNAL(triggered()), this, SLOT(addArticle()));
}
