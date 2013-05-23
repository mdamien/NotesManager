#include "notewidget.h"

NoteWidget::NoteWidget(const QString& tit, const QString& cont, QWidget *parent) : QWidget(parent)
{
    title = new QLineEdit(tit);
    content = new QTextEdit();
    content->setPlainText(cont);
}
