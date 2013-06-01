#include "imagewidget.h"
#include <QFileDialog>

ImageWidget::ImageWidget(Image* img,QWidget* parent):NoteWidget(parent),note(img)
{
    image = new QLabel(this);
    image->setPixmap(QPixmap(note->getPath()));
    description = new QTextEdit(note->getDescription());
    title->setText(note->getTitle());
    button = new QPushButton("Choose image");
    layout->addWidget(image);
    layout->addWidget(button);
    layout->addWidget(description);
    connect(description,SIGNAL(textChanged()),this,SLOT(updateNote()));
    connect(button,SIGNAL(clicked()),this,SLOT(chooseImage()));
}

void ImageWidget::updateNote()
{
    NoteWidget::updateNote();
    if(note->getDescription() != description->toPlainText()){
        NotesManager::getInstance()->getHistory()->addAndExec(
                    new ModifyBinaryDescription(note,description->toPlainText()));
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

void ImageWidget::chooseImage()
{
    QString path = QFileDialog::getOpenFileName();
    if(path != note->getPath())
    {
        image->setPixmap(QPixmap(path));
        NotesManager::getInstance()->getHistory()->addAndExec(
                    new ModifyBinaryPath(note,path));
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

Note* ImageWidget::getNote(){
    return note;
}

