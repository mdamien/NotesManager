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
#include "notesmanager.h"
#include "tag.h"
#include "tagmanager.h"

class NotesManager;

/*! \class NotesParser
 * \brief Classe permettant de charger les notes et les meta-fichiers stockée sur disque dur
 */
class NotesParser
{
public:
    NotesParser();
    Note* parseArticle(QTextStream* in,unsigned int id);
    Note* parseBinary(QTextStream* in,unsigned int id,QString type);
    Note* parseDocument(QTextStream* in,unsigned int id, QString path);
    Note* parseNote(QString path,unsigned int id);
    void parseWorkplace(); //put all notes in the NotesManager / +tags / +opened
private:
    void parseMetafile(QString path); //set witch note are opened
    void parseTags(QString path); // put all tags in the tagmanager

    NotesManager* nm;
};

#endif // NOTESPARSER_H
