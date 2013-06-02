#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "note.h"


/*! \class Video
 * \brief Classe concréte représentant une note contenant un titre et d'autres notes
 */
class Document : public Note
{
public:
    Document(const unsigned int id, const QString& title);
    Document(const unsigned int id, const QString& title, const QList<Note*>& listeNotes);
    Document(Document* d);
    void addSubNote(Note* n);
    void removeSubNote(const unsigned int i);
    void removeSubNote(Note* n);
    Note* getSubNote(const unsigned int i);
    unsigned int getNumberOfSubNotes() const;
    ~Document();
    void deleteEverySubNotes();

private :
    QList<Note*>* notes;
    void load();
    Document(const Document&); //On interdit la recopie à l'utilisateur
    void operator=(const Document&);
};

#endif // DOCUMENT_H
