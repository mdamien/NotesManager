#include "articlewidget.h"

ArticleWidget::ArticleWidget(Article* article,QWidget* parent):NoteWidget(parent),note(article)
{
    text = new QPlainTextEdit(note->getText());
    title->setText(note->getTitle());

    layout->addWidget(text);
    connect(text,SIGNAL(textChanged()), this, SLOT(updateNote()));
}

void ArticleWidget::updateNote()
{
    if(note->getTitle() != title->text() || note->getText() != text->toPlainText())
    {
        note->setTitle(title->text());
        note->setText(text->toPlainText());
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

Note* ArticleWidget::getNote()
{
    return note;
}
