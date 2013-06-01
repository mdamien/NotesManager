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
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QHBoxLayout* buttons = new QHBoxLayout();
    QPushButton* addArticleB = new QPushButton("Article");
    QPushButton* addDocumentB = new QPushButton("Document");
    QPushButton* addVideoB = new QPushButton("Video");
    QPushButton* addImageB = new QPushButton("Image");
    QPushButton* addAudioB = new QPushButton("Audio");
    buttonsLayout->addWidget(new QLabel("Add:"));
    buttons->addWidget(addArticleB);
    buttons->addWidget(addDocumentB);
    buttons->addWidget(addImageB);
    buttons->addWidget(addArticleB);
    buttons->addWidget(addAudioB);
    buttons->addWidget(addVideoB);
    buttonsLayout->addLayout(buttons);
    layout->addLayout(buttonsLayout);
    buttons->setAlignment(buttonsLayout,Qt::AlignLeft);

    connect(addArticleB,SIGNAL(clicked()),this,SLOT(addArticle()));
    connect(addDocumentB,SIGNAL(clicked()),this,SLOT(addDocument()));
    connect(addVideoB,SIGNAL(clicked()),this,SLOT(addVideo()));
    connect(addImageB,SIGNAL(clicked()),this,SLOT(addImage()));
    connect(addAudioB,SIGNAL(clicked()),this,SLOT(addAudio()));
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

void DocumentWidget::addAudio()
{
    addNote(new Audio(NotesManager::getInstance()->getNewId(),"Title"));
}
void DocumentWidget::addVideo()
{
    addNote(new Video(NotesManager::getInstance()->getNewId(),"Title"));
}
void DocumentWidget::addDocument()
{
    addNote(new Document(NotesManager::getInstance()->getNewId(),"Title"));
}
void DocumentWidget::addArticle()
{
    addNote(new Article(NotesManager::getInstance()->getNewId(),"Title"));
}
void DocumentWidget::addImage()
{
    addNote(new Image(NotesManager::getInstance()->getNewId(),"Title"));
}
