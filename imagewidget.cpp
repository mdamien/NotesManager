#include "imagewidget.h"
#include <QLabel>
#include <QPixmap>

ImageWidget::ImageWidget(const QString& filename, QWidget* parent) : QWidget(parent)
{
    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap(filename));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);

    setLayout(layout);
}
