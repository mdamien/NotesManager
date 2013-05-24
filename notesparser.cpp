#include "notesparser.h"

#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>
#include <iostream>

#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include "notesfactory.h"

Note* NotesParser::parseArticle(QTextStream* in,unsigned int id)
{
    QString title = in->readLine();
    QString content = in->readAll(); //TODO:Be careful to the export final \n (unit-test it)
    return new Article(id,title,content);
}

Note* NotesParser::parseBinary(QTextStream* in,unsigned int id,QString type)
{
    QString title = in->readLine();
    QString path = in->readLine();
    QString description = in->readAll();
    if(type == "IMAGE"){
        new Image(id,title,description,path);
    }else if(type == "VIDEO"){
        new Video(id,title,description,path);
    }else if(type == "AUDIO"){
        new Audio(id,title,description,path);
    }
    return NULL;
}

Note* NotesParser::parseDocument(QTextStream* in,unsigned int id,QString path)
{
    QString title = in->readLine();
    QList<QString> notes_s = in->readAll().split("\n");
    QList<Note*>* notes = new QList<Note*>;
    for (int i = 0; i < notes_s.size(); ++i) {
        Note* n = parseNote(path,notes_s.at(i).toInt());
        notes->append(n);
    }
    return new Document(id,title,*notes);
}

Note* NotesParser::parseNote(QString path,unsigned int id)
{
    QString filepath = path+"/"+QString::number(id)+".note";
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)) {
        return NULL;//TODO: return file.errorString : 404 FILE NOT FOUND! ^^
    }
    QTextStream in(&file);
    QString type = in.readLine();
    Note* n = NULL;
    if(type == "ARTICLE"){
        n = parseArticle(&in,id);
    }else if(type == "IMAGE" || type == "AUDIO" || type == "VIDEO"){
        n = parseBinary(&in,id,type);
    }else if(type == "DOCUMENT"){
        n = parseDocument(&in,id,path);
    }
    file.close();

    return n;
}

QList<Note*>* NotesParser::parseWorkplace(QString path)
{
    return new QList<Note*>();
}
