#include "mainwindow.h"
#include "imagewidget.h"
mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
    QFrame* frameEditor = new QFrame;
    QFrame* frameText = new QFrame;
    QFrame* frameHTML = new QFrame;
    QFrame* frameLatex = new QFrame;

    layoutEditor = new QVBoxLayout(frameEditor);
    layoutText = new QVBoxLayout(frameText);
    layoutHTML = new QVBoxLayout(frameHTML);
    layoutLatex = new QVBoxLayout(frameLatex);

    textText = new QTextEdit;
    textText->setReadOnly(true);
    layoutText->addWidget(textText);

    textHTML = new QTextEdit;
    textHTML->setReadOnly(true);
    layoutHTML->addWidget(textHTML);


    textLatex = new QTextEdit;
    textLatex->setReadOnly(true);
    layoutLatex->addWidget(textLatex);

    onglets = new QTabWidget;

    areaEditor = new QScrollArea(onglets);
    areaEditor->setWidgetResizable(true);
    areaEditor->setWidget(frameEditor);

    areaText = new QScrollArea(onglets);
    areaText->setWidgetResizable(true);
    areaText->setWidget(frameText);

    areaHTML = new QScrollArea(onglets);
    areaHTML->setWidgetResizable(true);
    areaHTML->setWidget(frameHTML);

    areaLatex = new QScrollArea(this);
    areaLatex->setWidgetResizable(true);
    areaLatex->setWidget(frameLatex);


    onglets->addTab(areaEditor, "Editor");
    onglets->addTab(areaText, "Text");
    onglets->addTab(areaHTML, "HTML");
    onglets->addTab(areaLatex, "LaTeX");

    setCentralWidget(onglets);
    ImageWidget* im = new ImageWidget("down.png", this);
    layoutEditor->addWidget(im);
    //Ajout des menus :

    //Fichier
    QMenu* menuFile = menuBar()->addMenu("&File");
    QAction* aNew = menuFile->addAction("&New");

    QMenu* menuAdd = menuFile->addMenu("&Add");
    QAction* aArticle = menuAdd->addAction("A&rticle");
    QAction* aDocument = menuAdd->addAction("&Document");
    QAction* aAudio = menuAdd->addAction("Audi&o");
    QAction* aImage = menuAdd->addAction("&Image");
    QAction* aVideo = menuAdd->addAction("&Video");

    QAction* aOpen = menuFile->addAction("&Open");
    QAction* aClose = menuFile->addAction("&Close");

    connect(aArticle, SIGNAL(triggered()), this, SLOT(addArticle()));

    //Edition
    QMenu* menuEdit = menuBar()->addMenu("&Edit");
    QAction* aUndo = menuEdit->addAction("&Undo");
    QAction* aRedo = menuEdit->addAction("&Redo");
    QAction* aCoppy = menuEdit->addAction("&Copy");
    QAction* aPaste = menuEdit->addAction("&Paste");

    //Affichage
    QMenu* menuView = menuBar()->addMenu("&Affichage");
    aEditor = menuView->addAction("E&ditor");
    aText = menuView->addAction("&Texte");
    aHTML = menuView->addAction("&HTML");
    aLatex = menuView->addAction("&LaTeX");

    //Aide
    QMenu* menuHelp = menuBar()->addMenu("He&lp");
    QAction* aAbout = menuHelp->addAction("A&bout");

    connect(onglets, SIGNAL(currentChanged(int)), this, SLOT(ongletChanged(int)));
    connect(menuView, SIGNAL(triggered(QAction*)), this, SLOT(displayView(QAction*)));
}

void mainWindow::ongletChanged(int onglet)
{
    if(onglet != 0) //Si on n'a pas cliqué sur l'Editor, on utilise les fonctions d'import
    {
        QTextEdit* current = onglets->currentWidget()->findChild<QTextEdit*>();
        QString s = "";

        switch(onglet)
        {
        case 1:    //ExportText
            for(NotesManager::Iterator it = NotesManager::getInstance()->begin(); it != NotesManager::getInstance()->end(); ++it)
            {
                s += (*it)->exportNote((*NotesManager::getInstance()->getExporter())["TextExport"]);
            }
            current->setPlainText(s);
            break;

        case 2 :   //ExportHTML
            for(NotesManager::Iterator it = NotesManager::getInstance()->begin(); it != NotesManager::getInstance()->end(); ++it)
            {
                s += (*it)->exportNote((*NotesManager::getInstance()->getExporter())["HTMLExport"]);
            }
            current->setPlainText(s);
            break;

        case 3 :   //ExportLaTeX
            break;
        }
    }
}
