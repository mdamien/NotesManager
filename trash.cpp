#include "trash.h"
#include "notesmanager.h"

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
    selection = new QSet<TrashedListItem*>();
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
    for(QSet<TrashedListItem*>::Iterator it = selection->begin(); it != selection->end(); ++it)
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

void Trash::addItem(Note* note)
{
    QListWidgetItem* item = new TrashedListItem(note);
    item->setCheckState(Qt::Unchecked);
    notes->insert(note);
    notesList->addItem(item);
}

void Trash::deleteSelection()
{
    Note* n = NULL;
    for(QSet<TrashedListItem*>::Iterator it = selection->begin(); it != selection->end(); ++it)
    {
        n = ((TrashedListItem*)(*it))->getNote();
        n->setLoaded(false);
        notes->remove(n);      //Suppression du pointeur vers la note de la corbeille
        NotesManager::getInstance()->deleteRessource(n);
        notesList->removeItemWidget(*it);
        delete(*it); //Désallocation du pointeur sur chaque TrashListItem
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
