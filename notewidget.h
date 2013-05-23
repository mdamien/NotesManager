#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(const QString& tit = "", const QString& cont = "", QWidget *parent = 0);
    
signals:
    
public slots:
    
protected :
    QLineEdit* title;
    QTextEdit* content;
};

#endif // NOTEWIDGET_H
