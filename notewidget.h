#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "note.h"
#include "notesmanager.h"

class NoteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoteWidget(QWidget* parent = 0);
    virtual Note* getNote() = 0;

signals:
    void titleChanged(QString q);
    void deleteClicked(NoteWidget* nw);

public slots:
    virtual void updateNote() = 0;
    void sendWidgetToDelete();

protected:
    QLineEdit* title;
    QVBoxLayout* layout;
    QPushButton* deleteButton;
};

#endif // NOTEWIDGET_H
