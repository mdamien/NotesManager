#ifndef NOTESFACTORY_H
#define NOTESFACTORY_H

#include <ctime>
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include <map>



class NotesFactory
{
public:
    NotesFactory();
    static unsigned int getNewId();
    virtual Note* buildNote(const unsigned int id, const QString& title) const = 0;
    virtual Note* buildNewNote(const QString& title) const = 0;
    virtual Note* buildNoteCopy(Note* note) const = 0;
    static std::map<QString, NotesFactory*>* getFactories();
};

#endif // NOTESFACTORY_H
