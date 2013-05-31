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
    if(note->getTitle() != title->text() || note->getDescription() != description->toPlainText())
    {
        note->setTitle(title->text());
        note->setDescription(description->toPlainText());
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
        note->setPath(path);
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

Note* ImageWidget::getNote(){
    return note;
}

