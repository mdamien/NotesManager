#include "article.h"

Article::Article(const unsigned int id, const QString& title, const QString& text) : Note(id, title), text(text)
{

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
