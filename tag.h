#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QSet>

#include "note.h"

/*! \class Tag
 * \brief Classe représentant un tag de note et contenant toutes les notes associés à ce tag
 */
class Tag
{
public:
    Tag(QString name);
    ~Tag();
    QString getName();
    void addNote(Note* note);
    void removeNote(Note* note);
    bool contains(Note* note);

    //Iterator
    class Iterator
    {
        friend class Tag;
    public :
        Iterator& operator++();
        Iterator& operator--();
        Note* operator*();
        bool operator==(const Iterator& it) const;
        bool operator!=(const Iterator& it) const;
    private :
        Iterator(const QSet<Note*>::Iterator& it);
        QSet<Note*>::Iterator itNotes;
    };

    Iterator begin();
    Iterator end();

private:
    QString name;
    QSet<Note*>* notes;
};


#endif // TAG_H
