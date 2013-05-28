#include "notesparser.h"

#include <QDebug>

#include "notesmanager.h"

NotesParser::NotesParser()
{
    nm = NotesManager::getInstance();
}

Note* NotesParser::parseArticle(QTextStream* in,unsigned int id)
{
    QString title = in->readLine();
    QString content = in->readAll();
    if(nm->getNoteByID(id) == NULL){
        Article* n = new Article(id,title,content);
        nm->addRessource(n);
    }
    return nm->getNoteByID(id);
}

Note* NotesParser::parseBinary(QTextStream* in,unsigned int id,QString type)
{
    QString title = in->readLine();
    QString path = in->readLine();
    QString description = in->readAll();
    if(nm->getNoteByID(id) == NULL){
        Note* n = NULL;
        if(type == "IMAGE"){
            n = new Image(id,title,description,path);
        }else if(type == "VIDEO"){
            n= new Video(id,title,description,path);
        }else if(type == "AUDIO"){
            n = new Audio(id,title,description,path);
        }
        nm->addRessource(n);
    }
    return nm->getNoteByID(id);
}

Note* NotesParser::parseDocument(QTextStream* in,unsigned int id,QString path)
{
    QString title = in->readLine();
    QList<QString> notes_s = in->readAll().split("\n");
    QList<Note*>* notes = new QList<Note*>;
    for (int i = 0; i < notes_s.size(); ++i) {
        if(notes_s.at(i).length()>0){
            Note* n = parseNote(path,notes_s.at(i).toUInt());
            if(n != NULL){
                notes->append(n);
            }
        }
    }
    if(nm->getNoteByID(id) == NULL){
        nm->addRessource(new Document(id,title,*notes));
    }
    return nm->getNoteByID(id);
}

Note* NotesParser::parseNote(QString path,unsigned int id)
{
    QString filepath = path+"/"+QString::number(id)+".note";
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File not found: " << filepath << "  E:" << file.errorString();
        return NULL;
    }
    QTextStream in(&file);
    QString type = in.readLine();
    Note* n = NULL;
    if(type == "ARTICLE")
    {
        n = parseArticle(&in,id);
    }
    else if(type == "IMAGE" || type == "AUDIO" || type == "VIDEO")
    {
        n = parseBinary(&in,id,type);
    }
    else if(type == "DOCUMENT")
    {
        n = parseDocument(&in,id,path);
    }
    file.close();

    return n;
}

void NotesParser::parseWorkplace()
{
    NotesManager::getInstance()->reset();
    TagManager::getInstance()->reset();
    QDir dir;
    dir.setCurrent(nm->getPath());
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName().contains(".note") && fileInfo.fileName() != ".notes")
        {
            parseNote(dir.absolutePath(),fileInfo.baseName().toUInt());
        }
    }
    parseMetafile(dir.absolutePath());
    parseTags(dir.absolutePath());
}

void NotesParser::parseMetafile(QString path)
{
    QString filepath = path+"/.notes";
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << ".notes not found: " << path << "  E:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    QList<QString> notes_s = in.readAll().split("\n");
    NotesManager* nm = NotesManager::getInstance();
    for (int i = 0; i < notes_s.size(); ++i) {
        Note* n = nm->getNoteByID(notes_s.at(i).toUInt());
        if(n != NULL){
            n->setLoaded(true);
        }
    }
}

void NotesParser::parseTags(QString path)
{
    QString filepath = path+"/.tags";
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << ".tags not found: " << path << "  E:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("|");

        Tag* tag = new Tag(fields.at(0));
        QStringList ids = fields.at(1).split(";");
        for (int i = 0; i < ids.size(); i++) {
            Note* n = NotesManager::getInstance()->getNoteByID(ids.at(i).toUInt());
            if(n != NULL){
                tag->addNote(n);
            }
        }
        TagManager::getInstance()->addTag(tag);
    }

    file.close();
}
