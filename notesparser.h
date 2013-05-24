#ifndef NOTESPARSER_H
#define NOTESPARSER_H

#include <QList>
#include "note.h"

//static helper for loading .note files and the workplace
class NotesParser
{
public:
    NotesParser();
    Note* parseArticle(QTextStream* in,unsigned int id);
    Note* parseBinary(QTextStream* in,unsigned int id,QString type);
    Note* parseDocument(QTextStream* in,unsigned int id,QString path);
    Note* parseNote(QString path, unsigned int id);
    void parseWorkplace(QString path); //put all notes in the NotesManager
    void parseMetafile(QString path); //set witch note are opened
    void parseTags(QString path); // put all tags in the tagmanager
};

#endif // NOTESPARSER_H
