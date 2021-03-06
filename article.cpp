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

Article::Article(Article* a) : Note(a->getId(), a->getTitle()), text(a->getText())
{

}

void Article::load()
{

}
