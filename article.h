#ifndef ARTICLE_H
#define ARTICLE_H

#include "note.h"

class Article : public Note
{
public:
    Article(const unsigned int id, const QString& title, const QString& text);
    QString getText() const;
    void setText(const QString& t);

private :
    QString text;
    Article(const Article&); //On interdit la recopie d'Article à l'utilisateur
    Article& operator=(const Article&); //De même avec op =
    void load();
};

#endif // ARTICLE_H
