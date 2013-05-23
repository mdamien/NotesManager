#include "mainwindow.h"
#include "imagewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
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

    //Ajout des menus :

    //Fichier
    QMenu* menuFile = menuBar()->addMenu("&File");
    QAction* aNew = menuFile->addAction("&New");

    QMenu* menuAdd = menuFile->addMenu("&Add");
    aArticle = menuAdd->addAction("A&rticle");
    aAudio = menuAdd->addAction("Audi&o");
    aImage = menuAdd->addAction("&Image");
    aVideo = menuAdd->addAction("&Video");

    QAction* aOpen = menuFile->addAction("&Open");
    QAction* aClose = menuFile->addAction("&Close");

    connect(menuAdd, SIGNAL(triggered(QAction*)), this, SLOT(addNote(QAction*)));

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

void MainWindow::ongletChanged(int onglet)
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

void MainWindow::displayView(QAction* a) //SLOT gérant le clic sur une action du menu du choix d'affichage : permet de n'utiliser qu'une méthode pour 4 actions
{
    if(a == aEditor)
    {
        onglets->setCurrentIndex(0);
    }
    else if(a == aText)
    {
        onglets->setCurrentIndex(1);
    }
    else if(a == aHTML)
    {
        onglets->setCurrentIndex(2);
    }
    else if(a == aLatex)
    {
        onglets->setCurrentIndex(3);
    }
}

void MainWindow::addNote(QAction* a) //SLOT gérant le clic sur une action du menu d'ajout de Note : permet de n'utiliser qu'une méthode pour plusieurs actions
{
    if(a == aArticle)
    {
        ArticleWidget* a = new ArticleWidget("Titre", "Contenu", this);
        layoutEditor->addWidget(a);
    }
    else if(a == aImage)
    {
        ImageWidget* im = new ImageWidget();
        layoutEditor->addWidget(im);
    }
    else if(a == aVideo)
    {
        VideoWidget* vw = new VideoWidget();
        layoutEditor->addWidget(vw);
    }
    else if(a == aAudio)
    {
        AudioWidget* audw = new AudioWidget();
        layoutEditor->addWidget(audw);
    }
}
