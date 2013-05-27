#include "notewidget.h"

NoteWidget::NoteWidget(QWidget* parent):QWidget(parent)
{
    layout = new QVBoxLayout(this);
    title = new QLineEdit();
    layout->addWidget(title);
    this->setLayout(layout);

    connect(title,SIGNAL(textChanged(QString)),this,SLOT(updateNote()));
    connect(title,SIGNAL(textChanged(QString)),this,SIGNAL(titleChanged(QString)));
}
