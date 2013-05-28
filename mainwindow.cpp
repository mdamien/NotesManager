#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>
#include <QDebug>
#include "savetextexport.h"
#include <QFileDialog>

MainWindow* MainWindow::mw = 0;

MainWindow* MainWindow::getInstance(QWidget *parent)
{
    if(mw){
        return mw;
    }
    else {
        mw = new MainWindow(parent);
        return mw;
    }
}

void MainWindow::deleteInstance()
{
    if(mw){
        delete mw;
        mw = 0;   //Remise du pointeur à 0
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nm = NotesManager::getInstance();
    tm = TagManager::getInstance();
    currentNote = NULL;

    updateNotesList();
    updateTagsList();
    tagSearch("");//pour remplir remplir une liste de tout les tags / notes

    connect(ui->tabs,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    connect(ui->menuAdd, SIGNAL(triggered(QAction*)), this, SLOT(addNote(QAction*)));
    connect(ui->actionNew, SIGNAL(triggered()),this,SLOT(newNote()));
    connect(ui->actionSave, SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionClose, SIGNAL(triggered()),this,SLOT(closeNote()));
    connect(ui->notes_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(loadSidebarNote(QListWidgetItem*)));
    connect(ui->tag_list, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(updateTag(QListWidgetItem*)));
    connect(ui->tag_set, SIGNAL(clicked()),this,SLOT(addTag()));
    connect(ui->tag_lineedit, SIGNAL(textChanged(QString)),this,SLOT(tagSearch(QString)));
    connect(ui->tag_search, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(loadSidebarNote(QListWidgetItem*)));
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

void MainWindow::updateTagsList(){
    ui->tag_list->clear();
    if(currentNote != NULL){
        for(TagManager::Iterator it = tm->begin();it != tm->end();++it){
            QListWidgetItem* item = new TagListItem((*it)->getName(),(*it));
            if((*it)->contains(currentNote->getNote())){
                item->setCheckState(Qt::Checked);
            }
            else{
                item->setCheckState(Qt::Unchecked);
            }
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            ui->tag_list->addItem(item);
        }
    }
}

void MainWindow::updateTag(QListWidgetItem *item)
{
    TagListItem* i = (TagListItem*)item;
    bool checked = i->checkState() == Qt::Checked;
    Tag* tag = i->getTag();
    if(currentNote != NULL){
        if(checked && !tag->contains(currentNote->getNote())){
            tag->addNote(currentNote->getNote());
        }
        if(!checked && tag->contains(currentNote->getNote())){
            tag->removeNote(currentNote->getNote());
        }
    }
}

void MainWindow::tagSearch(QString name)
{
    ui->tag_search->clear();
    for(TagManager::Iterator it = tm->begin();it != tm->end();++it){
        if((*it)->getName().contains(name)){
            for(Tag::Iterator it2 = (*it)->begin();it2 != (*it)->end();++it2){
                QListWidgetItem* item = new NoteListItem((*it)->getName() +" - "+ (*it2)->getTitle(),(*it2));
                ui->tag_search->addItem(item);
            }
        }
    }
}

void MainWindow::addTag()
{
    if(currentNote != NULL){
        QString txt = ui->tag_lineedit->text();
        if(txt.length() > 0){
            Tag* t = tm->getTag(txt);
            if (t == NULL){
                t = new Tag(txt);
                t->addNote(currentNote->getNote());
                tm->addTag(t);
            }else{
                t->addNote(currentNote->getNote());
            }
        }
        updateTagsList();
    }
}

void MainWindow::newNote()
{
    clearLayout(ui->editor_area->layout());
    currentNote = NULL;
    updateTagsList();
}

void MainWindow::closeNote()
{
    if(currentNote != NULL){
        currentNote->getNote()->setLoaded(false);
        clearLayout(ui->editor_area->layout());
        currentNote = NULL;
        updateNotesList();
        updateTagsList();
    }
}

void MainWindow::save()
{
    SaveTextExport().save();
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
    n->getNote()->setLoaded(true);
    updateNotesList();
    updateTagsList();
}

NoteWidget *MainWindow::makeWidget(Note *note, QWidget* parent)
{
    NoteWidget* n = NULL;
    if(typeid(*note) == typeid(Article))
        n = new ArticleWidget((Article*)note, parent);
    else if(typeid(*note) == typeid(Document))
        n = new DocumentWidget((Document*)note, parent);
    else if(typeid(*note) == typeid(Image))
        n = new ImageWidget((Image*)note, parent);
    else if(typeid(*note) == typeid(Audio))
        n = new AudioWidget((Audio*)note, parent);
    else if(typeid(*note) == typeid(Video))
        n = new VideoWidget((Video*)note, parent);
    else
        qDebug() << "ERROR:Note type not implemented yet in Qt Widgets";
    connect(n,SIGNAL(titleChanged(QString)),this,SLOT(updateNotesList()));
    return n;
}

void MainWindow::tabChanged(int i)
{
    if(currentNote != NULL){
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
        n = new Image(nm->getNewId(),"Titre Image","Description");
    }
    else if(a == ui->actionDocument)
    {
        n = new Document(nm->getNewId(),"Titre Document");
    }
    else if(a == ui->actionAudio)
    {
        n = new Audio(nm->getNewId(),"Titre Audio","Description");
    }
    else if(a == ui->actionVideo)
    {
        n = new Video(nm->getNewId(),"Titre Video","Description");
    }
    if(n == NULL){
        return;
    }
    nm->addRessource(n);

    NoteWidget* w = makeWidget(n,this);

    if(currentNote == NULL){
        n->setLoaded(true);
        loadNote(w);
        updateNotesList();
    }
    else{
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
