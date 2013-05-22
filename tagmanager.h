#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QString>
#include <QList>

#include "note.h"
#include "tag.h"

class TagManager : private QList<Tag*>
{
public:
    static TagManager* getInstance();
    static void deleteInstance();

    void addTag(QString name,Note* note);
    void removeTag(QString name);
    void removeTaggedNote(Note* note);
    QList<QString> getTags();
    QList<QString> getNoteTags(Note* note); //Tags of a Note
    Tag* getTag(QString name);
private:
    //Implémentation du design pattern Singleton
    TagManager();
    TagManager(const TagManager&);
    TagManager& operator=(const TagManager&);
    ~TagManager();

    static TagManager* tagManager;
};

#endif // TAGMANAGER_H
