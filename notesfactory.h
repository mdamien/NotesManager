#ifndef NOTESFACTORY_H
#define NOTESFACTORY_H

#include <ctime>
#include "note.h"
#include <QMap>

class NotesFactory
{
public:
    NotesFactory();
    unsigned int getNewId() const;
    virtual Note* buildNote(const unsigned int id, const QString& title) const = 0;
    virtual Note* buildNewNote(const QString& title) const = 0;
    virtual Note* buildNoteCopy(Note* note) const = 0;
   // static Qmap<QString, NotesFactory*>* getFactories();

private :
  //  Qmap<QString, NotesFactory*>* factories;
};

#endif // NOTESFACTORY_H
