#include "documentwidget.h"
#include "mainwindow.h"
#include <typeinfo>
#include <QDebug>

DocumentWidget::DocumentWidget(Document* doc,QWidget *parent):NoteWidget(parent),note(doc)
{
    title->setText(note->getTitle());
    childsLayout = new QVBoxLayout();
    layout->addLayout(childsLayout);
    for (unsigned int i = 0; i < note->getNumberOfSubNotes(); ++i)
    {
        addNote(note->getSubNote(i));
    }
}

void DocumentWidget::updateNote()
{
    if(note->getTitle() != title->text())
    {
        note->setTitle(title->text());
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

Note* DocumentWidget::getNote()
{
    return note;
}

void DocumentWidget::addNote(Note *n)
{
    addNoteWidget(MainWindow::getInstance()->makeWidget(n,this));
}

void DocumentWidget::addNoteWidget(NoteWidget *n)
{
    childsLayout->addWidget(n);
}
