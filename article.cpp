#include "article.h"

Article::Article(const unsigned int ID, const QString& title, const QString& text) : Note(id, title), text(text)
{
    if(ID == 0)
        id = NotesFactory::getNewId();
}

QString Article::getText() const
{
    return text;
}

void Article::setText(const QString& t)
{
    text = t;
}

void Article::load()
{
//A définir
}

Article::Article(Article* a) : Note(a->getId(), a->getTitle()), text(a->getText())
{

}
