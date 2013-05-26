#include "mainwindow.h"
#include "imagewidget.h"

MainWindow* MainWindow::mw = 0;

MainWindow* MainWindow::getInstance(QWidget *parent)
{
    if(mw)
    {
        return mw;
    }
    else
    {
        mw = new MainWindow(parent);
        return mw;
    }
}

void MainWindow::deleteInstance()
{
    if(mw)
    {
        delete mw;
        mw = 0;   //Remise du pointeur à 0
    }
}

MainWindow::~MainWindow()
{

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QFrame* frameEditor = new QFrame;
    QFrame* frameText = new QFrame;
    QFrame* frameHTML = new QFrame;
    QFrame* frameLatex = new QFrame;



    //
    QHBoxLayout* hLayout = new QHBoxLayout(frameEditor);
    QVBoxLayout* tagNotesLayout = new QVBoxLayout;

    notesList = new QListWidget;
    notesList->setMaximumWidth(150);
    tagNotesLayout->addWidget(notesList);
    notesList->setStyleSheet("* { background-color:rgb(50,100,150); padding: 7px ; color:rgb(255,255,255)}");
    //



    layoutEditor = new QVBoxLayout;
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








    hLayout->addLayout(tagNotesLayout);
 //   hLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding,QSizePolicy::Expanding ));
    hLayout->addLayout(layoutEditor);







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
    connect(aClose, SIGNAL(triggered()), this, SLOT(closeNote()));
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
                if((*it)->isLoaded())
                  s += (*it)->exportNote((*NotesManager::getInstance()->getExporter())["TextExport"]);
            }
            current->setPlainText(s);
            break;

        case 2 :   //ExportHTML
            for(NotesManager::Iterator it = NotesManager::getInstance()->begin(); it != NotesManager::getInstance()->end(); ++it)
            {
                if((*it)->isLoaded())
                  s += (*it)->exportNote((*NotesManager::getInstance()->getExporter())["HTMLExport"]);
            }
            current->setPlainText(s);
            break;

        case 3 :   //ExportLaTeX
            for(NotesManager::Iterator it = NotesManager::getInstance()->begin(); it != NotesManager::getInstance()->end(); ++it)
            {
                if((*it)->isLoaded())
                   s += (*it)->exportNote((*NotesManager::getInstance()->getExporter())["HTMLExport"]);
            }
            current->setHtml(s);
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
    NotesManager* nm = NotesManager::getInstance();

    if(layoutEditor->isEmpty())
    {
        //On crée un document si on a déjà une Note et qu'on ajoute une, on demande son titre à l'utilisateur, et il ne doit pas être vide
        QString noteTitle = "";
        do
        {
             noteTitle = QInputDialog::getText(this, "Note title", "Please, enter the title of the new note.");
             if(noteTitle == "")
                 QMessageBox::critical(this, "Non valide name", "Please enter a name !");
        }
        while(noteTitle == "");

        noteTitleEdit = new QLineEdit(noteTitle, this);

        layoutEditor->addWidget(noteTitleEdit);
    }

    //Ajout du widget demandé en fonction de l'action
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

void MainWindow::addNoteWidget(Note* n)
{
    if(Article* art = dynamic_cast<Article*> (n))
    {
        ArticleWidget* aw = new ArticleWidget(art->getTitle(), art->getText(), this);

        layoutEditor->addWidget(aw);
    }
    else if(Video* vid = dynamic_cast<Video*> (n))
    {
        VideoWidget* vw = new VideoWidget(vid->getPath(), vid->getTitle(), vid->getDescription(), this);
        layoutEditor->addWidget(vw);
    }
    else if(Image* im = dynamic_cast<Image*> (n))
    {
        ImageWidget* iw = new ImageWidget(im->getPath(), im->getTitle(), im->getDescription(), this);
        layoutEditor->addWidget(iw);
    }
    else if(Audio* aud = dynamic_cast<Audio*> (n))
    {
        AudioWidget* auw = new AudioWidget(aud->getPath(), aud->getTitle(), aud->getDescription(), this);
        layoutEditor->addWidget(auw);
    }
    notesList->addItem(new QListWidgetItem(n->getTitle()));

    connect(notesList,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changeNote())); //connect à faire : lier chaque QListWidgetItem à une note ?
}

void MainWindow::changeNoteTitle()
{
    QString noteTitle = "";
    do
    {
         noteTitle = QInputDialog::getText(this, "Note title", "Please, enter the title of the new note.");
         if(noteTitle == "")
             QMessageBox::critical(this, "Non valide name", "Please enter a name !");
    }
    while(noteTitle == "");

    //noteTitleLabel->setText("Note title : " + noteTitle);
}

void MainWindow::closeNote() //Fermeture de la note courante : penser à ajouter la sauvegarde...
{
    for(NotesManager::Iterator it = NotesManager::getInstance()->begin(); it != NotesManager::getInstance()->end(); ++it)
    {
        (*it)->setLoaded(false);
    }
    //layoutEditor
    QLayoutItem* child;
    child=layoutEditor->takeAt(0);
    while(child != 0)
    {
        if(child->widget()!=0)
            child->widget()->hide();
        layoutEditor->removeWidget(child->widget());
        delete child;
        child=layoutEditor->takeAt(0);
    }
}

void MainWindow::closeEvent(QCloseEvent* q)
{
 //   int answer = QMessageBox::question(this, "Closing NotesManager", "Would you like to save your not saved notes ?", QMessageBox::Yes | QMessageBox::No);
  //  if(answer == QMessageBox::Yes)
    {

    }
}
