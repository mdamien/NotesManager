#include "imagewidget.h"
#include <QFileDialog>


ImageWidget::ImageWidget(Image* img,QWidget* parent):BinaryWidget(img,parent)
{
    image = new QLabel(this);
    binaryLayout->addWidget(image);
    updateBinaryWidget();
}

void ImageWidget::updateBinaryWidget()
{
    image->setPixmap(QPixmap(note->getPath()));
}

void ImageWidget::changePath()
{
    path->setText(QFileDialog::getOpenFileName());
}
