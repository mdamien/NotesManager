#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"

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
    Note* note;
};

#endif // NOTEWIDGET_H
