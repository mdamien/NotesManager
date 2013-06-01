#include "notewidget.h"
#include "mainwindow.h"

NoteWidget::NoteWidget(QWidget* parent):QWidget(parent)
{
    layout = new QVBoxLayout(this);
    QHBoxLayout* layoutTitle = new QHBoxLayout;
    title = new QLineEdit();

    layoutTitle->addWidget(title);

    deleteButton = new QPushButton("Delete", this);
    layoutTitle->addWidget(deleteButton);

    layout->addLayout(layoutTitle);
    this->setLayout(layout);

    connect(title,SIGNAL(textChanged(QString)),this,SLOT(updateNote()));
    connect(title,SIGNAL(textChanged(QString)),this,SIGNAL(titleChanged(QString)));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(sendWidgetToDelete()));
    connect(this, SIGNAL(deleteClicked(NoteWidget*)), MainWindow::getInstance(), SLOT(deleteWidget(NoteWidget*)));
}

void NoteWidget::sendWidgetToDelete()
{
    emit deleteClicked(this);
}


void NoteWidget::updateNote()
{
    if(getNote()->getTitle() != title->text()){
        NotesManager::getInstance()->getHistory()->addAndExec(new ModifyNoteTitle(getNote(),title->text()));
        getNote()->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}
