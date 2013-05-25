#ifndef NOTESPARSER_H
#define NOTESPARSER_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>
#include <iostream>
#include <QDir>
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "notesfactory.h"
#include "notesmanager.h"
#include "tag.h"
#include "tagmanager.h"

//static helper for loading .note files and the workplace
class NotesParser
{
public:
    NotesParser();
    Note* parseArticle(QTextStream* in,unsigned int id);
    Note* parseBinary(QTextStream* in,unsigned int id,QString type);
    Note* parseDocument(QTextStream* in,unsigned int id,QString path);
    Note* parseNote(QString path, unsigned int id);
    void parseWorkplace(QString path); //put all notes in the NotesManager / +tags / +opened
private:
    void parseMetafile(QString path); //set witch note are opened
    void parseTags(QString path); // put all tags in the tagmanager
};

#endif // NOTESPARSER_H
