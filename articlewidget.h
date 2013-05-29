#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <QPlainTextEdit>

#include "notewidget.h"
#include "article.h"

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
