#include "note.h"
#include "exportstrategy.h"

Note::Note(const unsigned int id, const QString& title) : id(id), title(title)
{
    modified = false;
    loaded = true;
}

unsigned int Note::getId() const
{
    return id;
}

QString Note::getTitle() const
{
    return title;
}

void Note::setTitle(const QString& t)
{
    title = t;
}

bool Note::isModified() const
{
    return modified;
}

QString Note::exportNote(ExportStrategy* es) const
{
    return es->exportNote((Note*)this);
}

void Note::setLoaded(const bool b)
{
    loaded = b;
}

bool Note::isLoaded() const
{
    return loaded;
}
