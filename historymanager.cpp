#include "historymanager.h"

HistoryManager::HistoryManager()
{
    undo_stack = new QStack<Operation*>;
    redo_stack = new QStack<Operation*>;
}
HistoryManager::~HistoryManager()
{
    while (!undo_stack->isEmpty())
        delete undo_stack->pop();
    delete undo_stack;
    while (!redo_stack->isEmpty())
        delete redo_stack->pop();
    delete redo_stack;
}
void HistoryManager::redo()
{
    if(!redo_stack->empty()){
        Operation* op = redo_stack->pop();
        op->redo();
        undo_stack->push(op);
    }
}

void HistoryManager::undo()
{
    if(!undo_stack->empty()){
        Operation* op = undo_stack->pop();
        op->undo();
        redo_stack->push(op);
    }
}

void HistoryManager::addAndExec(Operation *op)
{
    op->redo();
    undo_stack->push(op);
}

ModifyNoteTitle::ModifyNoteTitle(Note *n, QString newTitle):note(n),oldTitle(n->getTitle()),newTitle(newTitle)
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
ModifyArticleText::ModifyArticleText(Article *n, QString newText):note(n),old(n->getText()),newText(newText)
{
}

void ModifyArticleText::redo()
{
    note->setText(newText);
}

void ModifyArticleText::undo()
{
    note->setText(old);
}

ModifyBinaryPath::ModifyBinaryPath(Binary *n, QString newText):note(n),old(n->getPath()),newText(newText)
{
}

void ModifyBinaryPath::redo()
{
    note->setPath(newText);
}

void ModifyBinaryPath::undo()
{
    note->setPath(old);
}
ModifyBinaryDescription::ModifyBinaryDescription(Binary *n, QString newText):note(n),old(n->getDescription()),newText(newText)
{
}

void ModifyBinaryDescription::redo()
{
    note->setDescription(newText);
}

void ModifyBinaryDescription::undo()
{
    note->setDescription(old);
}
