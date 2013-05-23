#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include "notewidget.h"

class ArticleWidget : public NoteWidget
{
public :
    ArticleWidget(const QString& tit = "", const QString& cont = "", QWidget* parent = 0);

protected :
};

#endif // ARTICLEWIDGET_H
