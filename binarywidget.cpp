#include "binarywidget.h"

BinaryWidget::BinaryWidget(Binary *bin, QWidget *parent):NoteWidget(parent),note(bin)
{
    description = new QTextEdit(note->getDescription());
    path = new QLineEdit(note->getPath());
    title->setText(note->getTitle());
    changePathB = new QPushButton("...", this);
    QHBoxLayout* pathLayout = new QHBoxLayout;
    pathLayout->addWidget(path);
    pathLayout->addWidget(changePathB);
    binaryLayout = new QHBoxLayout;
    layout->addLayout(binaryLayout);
    layout->addLayout(pathLayout);
    layout->addWidget(description);

    connect(changePathB, SIGNAL(clicked()), this, SLOT(changePath()));
    connect(path,SIGNAL(textChanged(QString)),this,SLOT(updateNote()));
    connect(description,SIGNAL(textChanged()),this,SLOT(updateNote()));
}

void BinaryWidget::updateNote()
{
    NoteWidget::updateNote();
    if(note->getPath() != path->text())
    {
        NotesManager::getInstance()->getHistory()->addAndExec(
                    new ModifyBinaryPath(note,path->text()));
        updateBinaryWidget();
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
    if(note->getDescription() != description->toPlainText()){
        NotesManager::getInstance()->getHistory()->addAndExec(
                    new ModifyBinaryDescription(note,description->toPlainText()));
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}
Note* BinaryWidget::getNote()
{
    return note;
}
