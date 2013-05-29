#include "history.h"
#include "mainwindow.h"

History::History()
{
    notesList = new QList<Note*>();
    widgetsList = new QList<NoteWidget*>();
}

void History::addNote(Note* n)
{
    notesList->append(n);
}

void History::updateNotesManger()
{
    if(notesList->size() > 0)
    {
        NotesManager* nm = NotesManager::getInstance();
        nm->deleteRessource(notesList->back());
        MainWindow::getInstance()->loadNote(widgetsList->back());
        widgetsList->removeLast();
        notesList->removeLast();
    }
}

void History::addWidget(NoteWidget* n)
{
    widgetsList->append(n);
}
