#include "savetextexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>
#include "tagmanager.h"
#include "notesmanager.h"
#include <QDir>
#include <QDebug>
#include "trash.h"

SaveTextExport::SaveTextExport()
{

}

QString SaveTextExport::base(QString name,Note* note,unsigned int n)
{
    return name.toUpper()+"\n"+note->getTitle()+"\n";
}
QString SaveTextExport::exportArticle(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note,titleLevel);
    str += note->getText();
    return str;
}

QString SaveTextExport::exportBinary(QString name,Binary* note,unsigned int titleLevel)
{
    QString str = base(name,note,titleLevel);
    str += note->getPath()+"\n";
    str += note->getDescription();
    return str;
}

QString SaveTextExport::exportImage(Image* note,unsigned int titleLevel)
{
    return exportBinary("Image",note,titleLevel);
}

QString SaveTextExport::exportVideo(Video* note,unsigned int titleLevel)
{
    return exportBinary("Video",note,titleLevel);
}

QString SaveTextExport::exportAudio(Audio* note,unsigned int titleLevel)
{
    return exportBinary("Audio",note,titleLevel);
}

QString SaveTextExport::exportTagsMetafile()
{
    TagManager* tm = TagManager::getInstance();
    QString str = "";
    for(TagManager::Iterator it = tm->begin();it != tm->end();++it)
    {
        str += (*it)->getName() + "|";
        for(Tag::Iterator it2 = (*it)->begin(); it2 != (*it)->end();++it2)
        {
            str += QString::number((*it2)->getId()) + ";";
        }
        str.remove(str.length()-1,1);
        str += "\n";
    }
    return str;
}

QString SaveTextExport::exportNotesMetafile()
{
    NotesManager* nm = NotesManager::getInstance();
    QString str = "";
    for(NotesManager::Iterator it = nm->begin();it != nm->end();++it)
    {
        if((*it)->isLoaded()){
            str += QString::number((*it)->getId())+"\n";
        }
    }
    Trash* trash = Trash::getInstance();
    for(Trash::Iterator it = trash->begin();it != trash->end();++it){
        str += "~"+QString::number((*it)->getId())+"\n";
    }
    return str;
}

void SaveTextExport::writeToFile(QString path,QString content){
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "ERROR: " << file.fileName() << "  E:" << file.errorString();
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
}

void SaveTextExport::save()
{
    SaveTextExport e;
    NotesManager* nm = NotesManager::getInstance();
    QString workplace = nm->getPath();

    nm->setNoteModified(false);

    //CLEAN
    QDir dir;
    dir.setCurrent(workplace);
    dir.setFilter(QDir::Hidden | QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName().contains(".note")
                || fileInfo.fileName() == ".notes"
                || fileInfo.fileName() == ".tags" ){
            QFile(fileInfo.absoluteFilePath()).remove();
        }
    }

    //SERIALIZE
    QString base = dir.absolutePath();
    writeToFile(base+"/.notes",e.exportNotesMetafile());
    writeToFile(base+"/.tags",e.exportTagsMetafile());
    for(NotesManager::Iterator it = nm->begin();it != nm->end();++it){
        writeToFile(base+"/"+QString::number((*it)->getId())+".note",e.exportNote(*it));
        (*it)->setModified(false);
    }
    Trash* trash = Trash::getInstance();
    for(Trash::Iterator it = trash->begin();it != trash->end();++it){
        writeToFile(base+"/"+QString::number((*it)->getId())+".note",e.exportNote(*it));
        (*it)->setModified(false);
    }
    nm->setNoteModified(false);
}
QString SaveTextExport::exportDocument(Document* note,unsigned int titleLevel)
{
    QString str = base("Document",note,titleLevel);
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++)
    {
       str += QString::number(note->getSubNote(i)->getId())+"\n"; //Ce sera à la fonction d'export, de bien exporter les sous-notes
    }
    return str;
}
