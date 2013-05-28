#include "historymanager.h"

HistoryManager::HistoryManager()
{
    undo_stack = new QStack<Operation*>;
    redo_stack = new QStack<Operation*>;
}
HistoryManager::~HistoryManager()
{
    /*
    while (!undo_stack->isEmpty())
        delete undo_stack->pop();
    delete undo_stack;
    while (!redo_stack->isEmpty())
        delete redo_stack->pop();
    delete redo_stack;
    */
}
void HistoryManager::redo()
{
    Operation* op = undo_stack->pop();
    op->redo();
    undo_stack->push(op);
}

void HistoryManager::undo()
{
    Operation* op = undo_stack->pop();
    op->undo();
    undo_stack->push(op);
}

void HistoryManager::addAndExec(Operation *op)
{
    op->redo();
    undo_stack->push(op);
}

ModifyNoteTitle::ModifyNoteTitle(Note *note, QString newTitle):note(note),oldTitle(note->getTitle()),newTitle(newTitle)
{
}

void ModifyNoteTitle::redo()
{
    note->setTitle(newTitle);
}

void ModifyNoteTitle::undo()
{
    note->setTitle(oldTitle);
}
