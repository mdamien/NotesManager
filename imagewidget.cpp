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
    note->setTitle(title->text());
    note->setDescription(description->toPlainText());
    note->setModified(true);
}

void ImageWidget::chooseImage()
{
    QString path = QFileDialog::getOpenFileName();
    image->setPixmap(QPixmap(path));
    note->setPath(path);
    note->setModified(true);
}

Note* ImageWidget::getNote(){
    return note;
}

