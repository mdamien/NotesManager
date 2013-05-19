#ifndef ARTICLEFACTORY_H
#define ARTICLEFACTORY_H

#include "notesfactory.h"

class ArticleFactory : public NotesFactory
{
public:
    ArticleFactory();
    Article* buildNote(const unsigned int id, const QString& title) const;
    Article* buildNewNote(const QString& title) const;
    Article* buildNoteCopy(Note* note) const;
};

#endif // ARTICLEFACTORY_H
