#include "tagmanager.h"

TagManager* TagManager::tagManager = 0;

TagManager::TagManager()
{
    tags = new QSet<Tag*>;
}

TagManager* TagManager::getInstance()
{
    if(!tagManager)
    {
        tagManager = new TagManager;
        return tagManager;
    }
    else
        return tagManager;
}

void TagManager::deleteInstance()
{
    if(tagManager)
    {
        delete tagManager;
        tagManager = 0;     //Remise du pointeur à 0
    }
}

void TagManager::addTag(Tag* t)
{
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        if((*it)->getName() == t->getName()){
            return;
        }
    }
    tags->insert(t);
}

void TagManager::removeTag(QString name)
{
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        if((*it)->getName() == name){
            tags->remove(*it);
            return;
        }
    }
}

void TagManager::removeTaggedNote(Note* note)
{
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        (*it)->removeNote(note);
        return;
    }
}

QList<QString> TagManager::getTags()
{
    QList<QString> l;
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        l.append((*it)->getName());
    }
    return l;
}

QList<QString> TagManager::getNoteTags(Note* note) //Tags of a Note
{
    QList<QString> l;
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        if((*it)->contains(note)){
            l.append((*it)->getName());
        }
    }
    return l;
}

Tag* TagManager::getTag(QString name) //Notes of a tag
{
    QList<Note*> l;
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        if((*it)->getName() == name){
            return *it;
        }
    }
    return NULL;
}
TagManager::~TagManager(){
    for(TagManager::Iterator it = this->begin(); it != this->end();++it){
        delete *it;
    }
    delete tags;
}

//Iterator

TagManager::Iterator TagManager::begin()
{
    return Iterator(tags->begin());
}

TagManager::Iterator TagManager::end()
{
    return Iterator(tags->end());
}

TagManager::Iterator::Iterator(const QSet<Tag*>::Iterator& it)
{
    itNotes = it;
}

TagManager::Iterator& TagManager::Iterator::operator++()
{
    itNotes++;
}

TagManager::Iterator& TagManager::Iterator::operator--()
{
    itNotes--;
}

Tag* TagManager::Iterator::operator*()
{
    return *itNotes;
}

bool TagManager::Iterator::operator==(const Iterator& it) const
{
    return itNotes == it.itNotes;
}

bool TagManager::Iterator::operator!=(const Iterator& it) const
{
    return itNotes != it.itNotes;
}
