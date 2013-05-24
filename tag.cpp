#include "tag.h"

Tag::Tag(QString name):name(name){
    notes = new QSet<Note*>;
}

Tag::~Tag()
{
    delete notes;
}

QString Tag::getName(){
    return name;
}

void Tag::addNote(Note* note){
    notes->insert(note);
}

void Tag::removeNote(Note* note){
     notes->remove(note);
}

bool Tag::contains(Note* note){
    return notes->contains(note);
}

//Iterator

Tag::Iterator Tag::begin()
{
    return Iterator(notes->begin());
}

Tag::Iterator Tag::end()
{
    return Iterator(notes->end());
}

Tag::Iterator::Iterator(const QSet<Note*>::Iterator& it)
{
    itNotes = it;
}

Tag::Iterator& Tag::Iterator::operator++()
{
    itNotes++;
}

Tag::Iterator& Tag::Iterator::operator--()
{
    itNotes--;
}

Note* Tag::Iterator::operator*()
{
    return *itNotes;
}

bool Tag::Iterator::operator==(const Iterator& it) const
{
    return itNotes == it.itNotes;
}

bool Tag::Iterator::operator!=(const Iterator& it) const
{
    return itNotes != it.itNotes;
}
