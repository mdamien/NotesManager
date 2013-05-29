#include "document.h"
#include "exportstrategy.h"

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

void Document::load()
{
    //A définir
}

void Document::removeSubNote(Note* n)
{
    notes->removeOne(n);
}
