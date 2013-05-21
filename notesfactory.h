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
    unsigned int getNewId() const;
    virtual Note* buildNote(const unsigned int id, const QString& title) const = 0;
    virtual Note* buildNewNote(const QString& title) const = 0;
    virtual Note* buildNoteCopy(Note* note) const = 0;
    static const std::map<QString, NotesFactory*>& getFactories();

private :
 //   std::map<QString, NotesFactory*>* factories;
};

#endif // NOTESFACTORY_H
