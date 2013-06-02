#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <QPlainTextEdit>

#include "notewidget.h"
#include "article.h"

/*! \class ArticleWidget
 * \brief Widget permettant la visualisation et l'édition d'une note de type Article dans l'interface graphique
 */
class ArticleWidget : public NoteWidget
{
public:
    ArticleWidget(Article* a,QWidget* parent = 0);
    Note* getNote();

signals:

public slots:
    void updateNote();

private:
    QPlainTextEdit* text;
    Article* note;
};

#endif // ARTICLEWIDGET_H
