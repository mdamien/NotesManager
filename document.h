#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "note.h"

class Document : public Note
{
public:
    Document(const unsigned int id, const QString& title);
    Document(const unsigned int id, const QString& title, const QList<Note*>& listeNotes);
    void addSubNote(Note* n);
    void removeSurNote(const unsigned int i);
    Note* getSubNote(const unsigned int i);
    unsigned int getNumberOfSubNotes() const;

private :
    QList<Note*>* notes;
    void load();
    Document(const Document&); //On interdit la recopie à l'utilisateur
    void operator=(const Document&);
};

#endif // DOCUMENT_H
