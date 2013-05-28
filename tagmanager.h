#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QString>
#include <QList>

#include "note.h"
#include "tag.h"

class TagManager
{
public:
    static TagManager* getInstance();
    static void deleteInstance();

    void addTag(Tag *t);
    void removeTag(QString name);
    void removeTaggedNote(Note* note);
    QList<QString> getTags();
    QList<QString> getNoteTags(Note* note); //Tags of a Note
    Tag* getTag(QString name);
    void reset();

    //Iterator
    class Iterator
    {
        friend class TagManager;
    public :
        Iterator& operator++();
        Iterator& operator--();
        Tag* operator*();
        bool operator==(const Iterator& it) const;
        bool operator!=(const Iterator& it) const;
    private :
        Iterator(const QSet<Tag*>::Iterator& it);
        QSet<Tag*>::Iterator itNotes;
    };

    Iterator begin();
    Iterator end();
private:
    //Implémentation du design pattern Singleton
    TagManager();
    TagManager(const TagManager&);
    TagManager& operator=(const TagManager&);
    ~TagManager();

    static TagManager* tagManager;
    QSet<Tag*>* tags;
};

#endif // TAGMANAGER_H
