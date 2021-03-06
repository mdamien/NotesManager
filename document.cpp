#include "document.h"
#include "exportstrategy.h"
#include "notesmanager.h"

Document::Document(const unsigned int id, const QString& title) : Note(id, title)
{
    notes = new QList<Note*>;
}

Document::Document(const unsigned int id, const QString& title, const QList<Note*>& listeNotes) : Note(id, title)
{
    notes = new QList<Note*>;
    for(unsigned int i =0; i<listeNotes.size(); i++)
    {
        notes->append(listeNotes.at(i));
    }
}

Document::Document(Document* d) : Note(d->id, d->title)
{
    notes = new QList<Note*>;
    for(unsigned int i =0; i<d->notes->size(); i++)
    {
        notes->append(d->notes->at(i));
    }
}

Document::~Document()
{
    delete notes;
}

void Document::addSubNote(Note* n)
{
    notes->append(n);
}

void Document::removeSubNote(const unsigned int i)
{
    notes->removeAt(i);
}

Note* Document::getSubNote(const unsigned int i)
{
    return notes->at(i);
}

unsigned int Document::getNumberOfSubNotes() const
{
    return notes->size();
}

void Document::removeSubNote(Note* n)
{
    notes->removeOne(n);
}

void Document::load()
{

}

/*!
 * \brief Supprime toutes les notes d'un document en demandant au NotesManager de les supprimer
 */
void Document::deleteEverySubNotes()
{
    while(notes->count())
    {
        NotesManager::getInstance()->deleteRessource(notes->at(0));
        notes->removeAt(0);
    }
}
