#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QStack>
#include "notesmanager.h"
#include "note.h"

class Operation{
public:
    virtual void redo() = 0;
    virtual void undo() = 0;
};

class HistoryManager
{
public:
    HistoryManager();
    ~HistoryManager();
    void addAndExec(Operation* op);
    void redo();
    void undo();
private:
    QStack<Operation*>* undo_stack;
    QStack<Operation*>* redo_stack;
};

class ModifyNoteAttribute :public Operation{
};

class ModifyNoteTitle :public ModifyNoteAttribute{
public:
    ModifyNoteTitle(Note* note,QString newTitle);
    void redo();
    void undo();
private:
    QString oldTitle;
    QString newTitle;
    Note* note;
};

class ModifyTag :public Operation{
};


#endif // HISTORYMANAGER_H
