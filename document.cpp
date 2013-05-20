#include "document.h"
#include "exportstrategy.h"

Document::Document(const unsigned int id, const QString& title) : Note(id, title)
{
    notes = new QList<Note*>;
}

Document::Document(const unsigned int id, const QString& title, const QList<Note*>& listeNotes) : Note(id, title)
{

}

Document::~Document()
{
    delete notes;
}

void Document::addSubNote(Note* n)
{
    notes->append(n);
}

void Document::removeSurNote(const unsigned int i)
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

QString Document::exportNote(ExportStrategy* es) const
{
    return es->exportNote((Document*)this);
}


void Document::load()
{
    //A définir
}
