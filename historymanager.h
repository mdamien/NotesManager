#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QStack>
#include "note.h"
#include "article.h"
#include "binary.h"

/*! \class Operation
 * \brief Opération basique et réversible
 */
class Operation{
public:
    virtual void redo() = 0;
    virtual void undo() = 0;
};

/*! \class HistoryManager
 * \brief Gestionnaire de l'historique des opérations
 */
class HistoryManager
{
public:
    HistoryManager();
    ~HistoryManager();
    void addAndExec(Operation* op);
    void redo();
    void undo();
private:
    HistoryManager(const HistoryManager&); //On interdit la recopie à l'utilisateur
    void operator=(const HistoryManager&);
    QStack<Operation*>* undo_stack;
    QStack<Operation*>* redo_stack;
};

/*! \class ModifyNoteTitle
 * \brief Opération de modification du titre d'une note
 */
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

/*! \class ModifyArticleText
 * \brief Opération de modification du texte d'un article
 */
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

/*! \class ModifyBinaryPath
 * \brief Opération de modification du chemin d'un binaire
 */
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

/*! \class ModifyBinaryDescription
 * \brief Opération de modification de la description d'un binaire
 */
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
