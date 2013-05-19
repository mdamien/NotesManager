#ifndef ARTICLEWIDGET_H
#define ARTICLEWIDGET_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>

class ArticleWidget : public QWidget
{
public :
    ArticleWidget(const QString& tit, const QString& cont, QWidget* parent = 0);

protected :
    QLineEdit* title;
    QTextEdit* content;
};

#endif // ARTICLEWIDGET_H
