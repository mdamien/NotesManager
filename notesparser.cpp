#include "notesparser.h"
#include <QDebug>

NotesParser::NotesParser()
{

}

Note* NotesParser::parseArticle(QTextStream* in,unsigned int id)
{
    QString title = in->readLine();
    QString content = in->readAll();
    NotesManager* nm = NotesManager::getInstance();
    if(nm->getNoteByID(id) == NULL){
        nm->addRessource(new Article(id,title,content));
    }

    return nm->getNoteByID(id);
}

Note* NotesParser::parseBinary(QTextStream* in,unsigned int id,QString type)
{
    QString title = in->readLine();
    QString path = in->readLine();
    QString description = in->readAll();
    NotesManager* nm = NotesManager::getInstance();
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
        Note* n = parseNote(path,notes_s.at(i).toInt());
        notes->append(n);
    }
    NotesManager* nm = NotesManager::getInstance();
    if(nm->getNoteByID(id) == NULL){
        nm->addRessource(new Document(id,title,*notes));
    }
    return nm->getNoteByID(id);
}

Note* NotesParser::parseNote(QString path,unsigned int id)
{
    QString filepath = path+"/"+QString::number(id)+".note";
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File not found: " << id << "  E:" << file.errorString();
        return NULL;
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

void NotesParser::parseWorkplace(QString path)
{
    QDir dir;
    dir.setCurrent(path);
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName().contains(".note") && fileInfo.fileName() != ".notes"){
            parseNote(path,fileInfo.baseName().toInt());
        }
    }
    parseMetafile(path);
    parseTags(path);
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
        Note* n = nm->getNoteByID(notes_s.at(i).toInt());
        if(n != NULL){
            //n->setOpened(true);
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
            Note* n = NotesManager::getInstance()->getNoteByID(ids.at(i).toInt());
            if(n != NULL){
                tag->addNote(n);
            }
        }
        TagManager::getInstance()->addTag(tag);
    }

    file.close();
}
