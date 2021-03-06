#include "trash.h"
#include "notesmanager.h"
#include "mainwindow.h"
#include "tagmanager.h"
#include <typeinfo>

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

/*!
 * \brief Affiche la fenêtre contenant le widget de la Trash
 */
void Trash::showTrash()
{
    this->show();
}

/*!
 * \brief Ajoute une note dans la Trash
 * \param note : Note à ajouter à la Trash
 * \param parent : Parent(document) de la note à ajouter à la Trash (peut être 0)
 */
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

/*!
 * \brief Supprime toutes les notes sélectionnées ("checkées") dans la liste des notes de la Trash. Supprimées du disque dur et du NotesManager.
 */
void Trash::deleteSelection()
{
    Note* n = NULL;
    for(QSet<QListWidgetItem*>::Iterator it = selection->begin(); it != selection->end(); ++it)
    {
        n = ((TrashedListItem*)(*it))->getNote();
        if(typeid(*n) == typeid(Document))        //Si le document à supprimer est un document : il faut supprimer chacune de ses sous-notes
        {
            ((Document*)n)->deleteEverySubNotes();
        }
        notes->remove(n);      //Suppression du pointeur vers la note de la corbeille
        NotesManager::getInstance()->deleteRessource(n);
        notesList->removeItemWidget(*it);
        delete(*it); //Désallocation du pointeur sur chaque TrashListItem
        TagManager::getInstance()->removeTaggedNote(n);
        NotesManager::getInstance()->setNoteModified();
    }

    selection->clear(); //On vide le QSet, chaque pointeur ayant été désalloué correctement plus tôt
}

/*!
 * \brief Restaure toutes les notes sélectionnées ("checkées") dans la liste des notes de la Trash. Elles sont rechargées dans la MainWindow.
 */
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

/*!
 * \brief Ajoute ou supprime la note sur laquelle l'utilisateur a clické, en fonction de l'état ("checkée" ou non)
 * \param item : Contient une note qui permet une synchronisation interface-objet facile.
 */
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
