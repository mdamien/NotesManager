#include "trash.h"
#include "notesmanager.h"
#include "mainwindow.h"
#include "tagmanager.h"

Trash* Trash::trash = 0;

Trash::Trash(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;

    QPushButton* deleteSelection = new QPushButton("Delete selection");
    QPushButton* restoreSelection = new QPushButton("Restore selection");

    buttonsLayout->addWidget(deleteSelection);
    buttonsLayout->addWidget(restoreSelection);

    layout->addLayout(buttonsLayout);

    notes = new QSet<Note*>();
    selection = new QSet<QListWidgetItem*>();
    notesList = new QListWidget(this);

    layout->addWidget(notesList);

    setLayout(layout);

    connect(deleteSelection, SIGNAL(clicked()), this, SLOT(deleteSelection()));
    connect(restoreSelection, SIGNAL(clicked()), this, SLOT(restoreSelection()));
    connect(notesList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(addToSelection(QListWidgetItem*)));
}

Trash::~Trash()
{
    delete notes;
    delete notesList;
    for(QSet<QListWidgetItem*>::Iterator it = selection->begin(); it != selection->end(); ++it)
    {
        delete(*it); //Désallocation du pointeur sur chaque TrashListItem
    }
    delete selection;
}

Trash* Trash::getInstance(QWidget *parent)
{
    if(!trash)
    {
        trash = new Trash(parent);
    }
    return trash;
}

void Trash::deleteInstance()
{
    if(trash)
    {
        delete trash;
        trash = 0;
    }
}


void Trash::showTrash()
{
    this->show();
}

void Trash::addItem(Note* note, Document* parent)
{
    QListWidgetItem* item = NULL;

    if(!parent)
        item = new TrashedListItem(note);
    else
        item = new TrashedSubNoteListItem(note, parent);

    item->setCheckState(Qt::Unchecked);
    notes->insert(note);
    notesList->addItem(item);
}

void Trash::deleteSelection()
{
    Note* n = NULL;
    for(QSet<QListWidgetItem*>::Iterator it = selection->begin(); it != selection->end(); ++it)
    {
        n = ((TrashedListItem*)(*it))->getNote();
        n->setLoaded(false);
        notes->remove(n);      //Suppression du pointeur vers la note de la corbeille
        NotesManager::getInstance()->deleteRessource(n);
        notesList->removeItemWidget(*it);
        delete(*it); //Désallocation du pointeur sur chaque TrashListItem
        QFile::remove(QString(n->getId()));
        TagManager::getInstance()->removeTaggedNote(n);
        NotesManager::getInstance()->setNoteModified();
    }
//    selection->clear(); //Suppression de chaque widget de la selection

    selection->clear(); //On vide le QSet, chaque pointeur ayant été désalloué correctement plus tôt

 //   notesList->clear();
/*
    for(QSet<Note*>::Iterator it = notes->begin(); it != notes->end(); ++it)
    {
        this->addItem(*it);
    }*/
}

void Trash::restoreSelection()
{
    Note* n = NULL;
    for(QSet<QListWidgetItem*>::Iterator it = selection->begin(); it != selection->end(); ++it)
    {
        n = ((TrashedListItem*)(*it))->getNote();

        if(typeid(**it) == typeid(TrashedSubNoteListItem)) //On regarde si cette note était une sous-note d'un document
        {
            TrashedSubNoteListItem* item = (TrashedSubNoteListItem*)(*it);
            if(Document* d = (Document*) NotesManager::getInstance()->getNoteByID(item->getParentDocument()->getId())) //Test pour savoir si le document existe toujours
                d->addSubNote(n);
            else
                n->setLoaded(true);        //S'il n'existe pas, on recharge la note séparément
        }
        else
        {
            n->setLoaded(true);
        }
        notes->remove(n);
        notesList->removeItemWidget(*it);
        delete(*it);
        NotesManager::getInstance()->setNoteModified();
    }
    selection->clear();
    MainWindow::getInstance()->updateNotesList();
}

void Trash::addToSelection(QListWidgetItem* item)
{
    TrashedListItem* i = (TrashedListItem*) item; //Cast de l'item en notre item personnalisé

    if(i->checkState() == Qt::Checked)
    {
        selection->insert(i);
    }
    else
    {
        if(selection->contains(i))
            selection->remove(i);
    }
}

//Iterator

Trash::Iterator Trash::begin()
{
    return Iterator(notes->begin());
}

Trash::Iterator Trash::end()
{
    return Iterator(notes->end());
}

Trash::Iterator::Iterator(const QSet<Note*>::Iterator& it)
{
    itNotes = it;
}

Trash::Iterator& Trash::Iterator::operator++()
{
    itNotes++;
}

Trash::Iterator& Trash::Iterator::operator--()
{
    itNotes--;
}

Note* Trash::Iterator::operator*()
{
    return *itNotes;
}

bool Trash::Iterator::operator==(const Iterator& it) const
{
    return itNotes == it.itNotes;
}

bool Trash::Iterator::operator!=(const Iterator& it) const
{
    return itNotes != it.itNotes;
}
