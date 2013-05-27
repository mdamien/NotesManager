#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include "note.h"

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(QWidget* parent = 0);
    virtual Note* getNote() = 0;
signals:
    
public slots:
    virtual void updateNote() = 0;
protected:
    QLineEdit* title;
    QVBoxLayout* layout;
};

#endif // NOTEWIDGET_H
