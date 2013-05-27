#include "articlewidget.h"

ArticleWidget::ArticleWidget(Article* article,QWidget* parent):NoteWidget(parent),note(article)
{
    text = new QTextEdit(note->getText());
    title->setText(note->getTitle());

    layout->addWidget(text);
    connect(text,SIGNAL(textChanged()),this,SLOT(updateNote()));
}

void ArticleWidget::updateNote()
{
    note->setTitle(title->text());
    note->setText(text->toPlainText());
    //note->setModified(true);
}

Note* ArticleWidget::getNote(){
    return note;
}

