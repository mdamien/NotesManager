#ifndef NOTESFACTORY_H
#define NOTESFACTORY_H

#include <ctime>
#include "note.h"

class NotesFactory
{
public:
    NotesFactory();
    unsigned int getNewId() const;
    Note* buildNote(const unsigned int id, const QString& title) const = 0;
    Note* buildNewNote(const QString& title) const = 0;
    Note* buildNoteCopy(Note* note) const = 0;
    static map<QString, NoteFactory*>* getFactories();

private :
    map<QString, NotesFactory*>* factories;
};

#endif // NOTESFACTORY_H
