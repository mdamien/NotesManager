#include "documentwidget.h"
#include "mainwindow.h"
#include <typeinfo>
#include <QDebug>
#include <QSpacerItem>

DocumentWidget::DocumentWidget(Document* doc,QWidget *parent):NoteWidget(parent),note(doc)
{
    title->setText(note->getTitle());
    childsLayout = new QVBoxLayout();
    layout->addLayout(childsLayout);
    for (unsigned int i = 0; i < note->getNumberOfSubNotes(); ++i)
    {
        addNote(note->getSubNote(i));
    }
    QSpacerItem* spacer = new QSpacerItem(0,0,QSizePolicy::Expanding);
    QHBoxLayout* buttons = new QHBoxLayout();
    QPushButton* addArticleB = new QPushButton("Article");
    QPushButton* addDocumentB = new QPushButton("Document");
    QPushButton* addVideoB = new QPushButton("Video");
    QPushButton* addImageB = new QPushButton("Image");
    QPushButton* addAudioB = new QPushButton("Audio");
    buttons->addSpacerItem(spacer);
    buttons->addWidget(new QLabel("Add:"));
    buttons->addWidget(addArticleB);
    buttons->addWidget(addDocumentB);
    buttons->addWidget(addImageB);
    buttons->addWidget(addAudioB);
    buttons->addWidget(addVideoB);
    layout->addLayout(buttons);
    buttons->setAlignment(layout,Qt::AlignLeft);

    connect(addArticleB,SIGNAL(clicked()),this,SLOT(addArticle()));
    connect(addDocumentB,SIGNAL(clicked()),this,SLOT(addDocument()));
    connect(addVideoB,SIGNAL(clicked()),this,SLOT(addVideo()));
    connect(addImageB,SIGNAL(clicked()),this,SLOT(addImage()));
    connect(addAudioB,SIGNAL(clicked()),this,SLOT(addAudio()));
}

/*!
 * \brief Renvoie la note que contient le widget
 * \return Note contenue par le widget.
 */
Note* DocumentWidget::getNote()
{
    return note;
}

/*!
 * \brief Crée un widget en fonction de la note passée en paramètre et l'ajoute au layout du document
 * \param n : Note à ajouter au layout
 */
void DocumentWidget::addNote(Note *n)
{
    addNoteWidget(MainWindow::getInstance()->makeWidget(n,this));
}

/*!
 * \brief Ajoute un widget de type NoteWidget au layout du document
 * \param n : Widget à ajouter au layout.
 */
void DocumentWidget::addNoteWidget(NoteWidget *n)
{
    childsLayout->addWidget(n);
}

/*!
 * \brief Ajoute un widget audio au layout du document
 */
void DocumentWidget::addAudio()
{
    Note* n = new Audio(NotesManager::getInstance()->getNewId(),"Title");
    note->addSubNote(n);
    NotesManager::getInstance()->addRessource(n);
    addNote(n);
}

/*!
 * \brief Ajoute un widget vidéo au layout du document
 */
void DocumentWidget::addVideo()
{
    Note* n = new Video(NotesManager::getInstance()->getNewId(),"Title");
    note->addSubNote(n);
    NotesManager::getInstance()->addRessource(n);
    addNote(n);
}

/*!
 * \brief Ajoute un widget document au layout du document
 */
void DocumentWidget::addDocument()
{
    Note* n = new Document(NotesManager::getInstance()->getNewId(),"Title");
    note->addSubNote(n);
    NotesManager::getInstance()->addRessource(n);
    addNote(n);
}

/*!
 * \brief Ajoute un widget article au layout du document
 */
void DocumentWidget::addArticle()
{
    Note* n = new Article(NotesManager::getInstance()->getNewId(),"Title");
    note->addSubNote(n);
    NotesManager::getInstance()->addRessource(n);
    addNote(n);
}

/*!
 * \brief Ajoute un widget image au layout du document
 */
void DocumentWidget::addImage()
{
    Note* n = new Image(NotesManager::getInstance()->getNewId(),"Title");
    note->addSubNote(n);
    NotesManager::getInstance()->addRessource(n);
    addNote(n);
}
