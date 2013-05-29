#ifndef HISTORY_H
#define HISTORY_H

#include "notesmanager.h"
#include "notewidget.h"

class History
{
private :
    QList<Note*>* notesList;
    QList<NoteWidget*>* widgetsList;

public:
    History();
    void addNote(Note* n);
    void updateNotesManger();
    void addWidget(NoteWidget* n);
};

#endif // HISTORY_H
