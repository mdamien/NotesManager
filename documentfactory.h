#ifndef DOCUMENTFACTORY_H
#define DOCUMENTFACTORY_H

#include "notesfactory.h"

class DocumentFactory : public NotesFactory
{
public:
    DocumentFactory();
    Note* buildNote(const unsigned int id, const QString& title) const;
    Note* buildNewNote(const QString& title) const;
    Note* buildNoteCopy(Note* note) const;
};

#endif // DOCUMENTFACTORY_H
