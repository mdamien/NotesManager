#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nm = NotesManager::getInstance();
    tm = TagManager::getInstance();
    currentNote = NULL;

    currentNote = makeWidget(nm->getNoteByID(3),this);
    ui->editor_area->layout()->addWidget(currentNote);

    updateNotesList();


    for(TagManager::Iterator it = tm->begin();it != tm->end();++it){
        ui->tag_list->addItem((*it)->getName());
    }

    connect(ui->tabs,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    connect(ui->menuAdd, SIGNAL(triggered(QAction*)), this, SLOT(addNote(QAction*)));
    connect(ui->notes_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(loadSidebarNote(QListWidgetItem*)));
}
void MainWindow::updateNotesList(){
    ui->notes_list->clear();
    for(NotesManager::Iterator it = nm->begin();it != nm->end();++it){
        if((*it)->isLoaded()){
            QListWidgetItem* item = new NoteListItem((*it)->getTitle(),(*it));
            ui->notes_list->addItem(item);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadNote(NoteWidget *n)
{
    clearLayout(ui->editor_area->layout());
    ui->editor_area->layout()->addWidget(n);
    currentNote = n;
}

NoteWidget *MainWindow::makeWidget(Note *note, QWidget* parent)
{
    if(typeid(*note) == typeid(Article))
        return new ArticleWidget((Article*)note, parent);
    else if(typeid(*note) == typeid(Document))
        return new DocumentWidget((Document*)note, parent);
    else if(typeid(*note) == typeid(Image))
        return new ImageWidget((Image*)note, parent);
    else
        qDebug() << "ERROR:Note type not implemented yet in Qt Widgets";
    return NULL;
}

void MainWindow::tabChanged(int i)
{
    switch(i)
    {
    case 1:    //ExportText
        ui->text_textedit->setPlainText(currentNote->getNote()->exportNote(nm->getExporter("Text")));
        break;
    case 2 :   //ExportHTML
        ui->html_textedit->setHtml(currentNote->getNote()->exportNote(nm->getExporter("HTML")));
        break;
    case 3 :   //ExportLaTeX
        ui->latex_textedit->setPlainText(currentNote->getNote()->exportNote(nm->getExporter("LaTeX")));
        break;
    }
}
void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        else if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

//TODO: TOO much magic happens here
void MainWindow::addNote(QAction* a)
{
    NotesManager* nm = NotesManager::getInstance();

    Note* n = NULL;

    if(a == ui->actionArticle)
    {
        n = new Article(nm->getNewId(),"Titre Article","Contenu");
    }
    else if(a == ui->actionImage)
    {
        n = new Image(nm->getNewId(),"Titre Image","Contenu","");
    }
    else if(a == ui->actionDocument)
    {
        n = new Document(nm->getNewId(),"Titre Dcoument");
    }

    if(n == NULL){
        return;
    }
    nm->addRessource(n);

    NoteWidget* w = makeWidget(n,this);

    if(currentNote == NULL || ui->editor_area->layout()->isEmpty()){
        loadNote(w);
    }
    if(currentNote != NULL)
    {
        if(QString(currentNote->metaObject()->className()) == "DocumentWidget"){
            ((DocumentWidget*)currentNote)->addNoteWidget(w);
            ((Document*)((DocumentWidget*)currentNote)->getNote())->addSubNote(n);
        }else{
            Document* d = new Document(nm->getNewId(),"Document");
            nm->addRessource(d);
            d->addSubNote(currentNote->getNote());
            currentNote->getNote()->setLoaded(false);
            d->setLoaded(true);
            d->addSubNote(n);
            loadNote(makeWidget(d,this));
            updateNotesList();
        }
    }
}

void MainWindow::loadSidebarNote(QListWidgetItem *item)
{
    NoteListItem* i = (NoteListItem*) item;
    loadNote(makeWidget(i->getNote(),this));
    ui->tabs->setCurrentIndex(0);
}
