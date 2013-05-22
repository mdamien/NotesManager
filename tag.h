#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QList>

#include "note.h"

class Tag : private QList<Note*>
{
public:
    Tag(QString name);
    QString getName();
    void addNote(Note* note);
    void removeNote(Note* note);
    unsigned int find(Note* note);
    Tag::Iterator begin();
    Tag::Iterator end();
private:
    QString name;
};


#endif // TAG_H
