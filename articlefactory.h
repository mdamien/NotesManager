#ifndef ARTICLEFACTORY_H
#define ARTICLEFACTORY_H

#include "notesfactory.h"
#include "article.h"

class ArticleFactory : public NotesFactory
{
public:
    ArticleFactory();
    Note* buildNote(const unsigned int id, const QString& title) const;
    Note* buildNewNote(const QString& title) const;
    Note* buildNoteCopy(Article* article) const;
};

#endif // ARTICLEFACTORY_H
