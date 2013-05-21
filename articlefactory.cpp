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

Note* ArticleFactory::buildNoteCopy(Note* note) const
{
    if(note = dynamic_cast<Article*> (note))    //Ne pas copier quelque chose qui n'est pas un Article
      return new Article((Article*) note);

    return 0;
}
