#include "articlefactory.h"

ArticleFactory::ArticleFactory()
{

}

Note* ArticleFactory::buildNote(const unsigned int id, const QString& title) const
{
    return new Article(id, title);
}

Note* ArticleFactory::buildNewNote(const QString& title) const
{
    return new Article(getNewId(), title);
}

Note* ArticleFactory::buildNoteCopy(Article* article) const
{
    return new Article(article);
}
