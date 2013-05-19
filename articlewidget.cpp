#include "articlewidget.h"

using namespace std;

ArticleWidget::ArticleWidget(const QString& tit, const QString& cont,QWidget* parent) : QWidget(parent)
{
    title = new QLineEdit(tit);
    content = new QTextEdit();
    content->setPlainText(cont);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(content);

    setLayout(layout);
}
