#include "tagmanager.h"

TagManager::TagManager()
{

}

void TagManager::addTag(QString name,Note* note)
{
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        if((*it)->getName() == name){
            return;
        }
    }
    Tag* t = new Tag(name);
    t->addNote(note);
    this->append(t);
}

void TagManager::removeTag(QString name)
{
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        if((*it)->getName() == name){
            this->removeOne(*it);
            return;
        }
    }
}

void TagManager::removeTaggedNote(Note* note)
{
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        (*it)->removeNote(note);
        return;
    }
}

QList<QString> TagManager::getTags()
{
    QList<QString> l;
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        l.append((*it)->getName());
    }
    return l;
}

QList<QString> TagManager::getNoteTags(Note* note) //Tags of a Note
{
    QList<QString> l;
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        if((*it)->find(note) != -1){
            l.append((*it)->getName());
        }
    }
    return l;
}

Tag* TagManager::getTag(QString name) //Notes of a tag
{
    QList<Note*> l;
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        if((*it)->getName() == name){
            return *it;
        }
    }
    return NULL;
}
TagManager::~TagManager(){
    for(TagManager::Iterator it = this->begin(); it != this->end();it++){
        delete *it;
    }
}
