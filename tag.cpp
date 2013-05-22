#include "tag.h"

Tag::Tag(QString name):name(name){

}

QString Tag::getName(){
    return name;
}

void Tag::addNote(Note* note){
    this->append(note);
}

void Tag::removeNote(Note* note){
    this->removeOne(note);
}

unsigned int Tag::find(Note* note){
    return this->indexOf(note);
}

Tag::Iterator Tag::begin(){
    return this->begin();
}
Tag::Iterator Tag::end(){
    return this->end();
}
