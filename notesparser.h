#ifndef NOTESPARSER_H
#define NOTESPARSER_H

#include <QList>
#include "note.h"

//static helper for loading .note files
class NotesParser
{
public:
    static Note* parseArticle(QTextStream* in,unsigned int id);
    static Note* parseBinary(QTextStream* in,unsigned int id,QString type);
    static Note* parseDocument(QTextStream* in,unsigned int id,QString path);
    static Note* parseNote(QString path, unsigned int id);
    static QList<Note*>* parseWorkplace(QString path);
    //TODO: parse metafile
private:
    NotesParser();
};

#endif // NOTESPARSER_H
