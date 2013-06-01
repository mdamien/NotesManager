#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QStack>
#include "note.h"
#include "article.h"
#include "binary.h"

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
    //TODO Copy
    QStack<Operation*>* undo_stack;
    QStack<Operation*>* redo_stack;
};

class ModifyNoteTitle : public Operation{
public:
    ModifyNoteTitle(Note* note,QString newTitle);
    void redo();
    void undo();
private:
    QString oldTitle;
    QString newTitle;
    Note* note;
};

class ModifyArticleText : public Operation{
public:
    ModifyArticleText(Article* note,QString newText);
    void redo();
    void undo();
private:
    QString old;
    QString newText;
    Article* note;
};

class ModifyBinaryPath : public Operation{
public:
    ModifyBinaryPath(Binary* note,QString newText);
    void redo();
    void undo();
private:
    QString old;
    QString newText;
    Binary* note;
};

class ModifyBinaryDescription : public Operation{
public:
    ModifyBinaryDescription(Binary* note,QString newText);
    void redo();
    void undo();
private:
    QString old;
    QString newText;
    Binary* note;
};


#endif // HISTORYMANAGER_H
