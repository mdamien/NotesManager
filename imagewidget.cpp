#include "imagewidget.h"

ImageWidget::ImageWidget(const QString& filename, const QString& tit, const QString& desc, QWidget* parent) : QWidget(parent), filename(filename)
{
    image = new QLabel(this);
    image->setPixmap(QPixmap(filename));

    title = new QLineEdit(tit);
    description = new QTextEdit(desc);
    path = new QPushButton("Set Image", this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(image);
    layout->addWidget(path);
    layout->addWidget(description);

    setLayout(layout);
    QObject::connect(path, SIGNAL(clicked()), this, SLOT(openExplorer()));
}

void ImageWidget::openExplorer()
{
    image->setPixmap(QPixmap(QFileDialog::getOpenFileName()));
}
