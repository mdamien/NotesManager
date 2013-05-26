#include "imagewidget.h"

ImageWidget::ImageWidget(const QString& filePath, const QString& tit, const QString& desc, QWidget* parent) : NoteWidget(tit, desc, parent), filePath(filePath)
{
    image = new QLabel(this);
    image->setPixmap(QPixmap(filePath));

    path = new QPushButton("Set Image", this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(image);
    layout->addWidget(path);
    layout->addWidget(content);

    note = new Image(NotesFactory::getNewId(), tit, desc, filePath);
    NotesManager::getInstance()->addRessource(note);

    setLayout(layout);
    QObject::connect(path, SIGNAL(clicked()), this, SLOT(openExplorer()));
}

void ImageWidget::openExplorer()
{
    image->setPixmap(QPixmap(QFileDialog::getOpenFileName()));
}
