#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QTextEdit>
#include <QPushButton>
#include "notewidget.h"
#include "document.h"

class DocumentWidget : public NoteWidget
{
    Q_OBJECT

public:
    DocumentWidget(Document* a,QWidget* parent = 0);
    Note* getNote();
    void addNote(Note* n);
    void addNoteWidget(NoteWidget* n);

signals:

private:
    Document* note;
    QVBoxLayout* childsLayout;
};

#endif // DOCUMENTWIDGET_H
