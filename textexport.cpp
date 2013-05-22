#include "textexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>

TextExport::TextExport()
{
}

QString TextExport::base(QString name,Note* note,unsigned int n){
    return name +":\n"+" ID:"+QString::number(note->getId())+"\n"
            +" Title:"+note->getTitle() + "\n";
}
QString TextExport::exportArticle(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note,titleLevel);
    str += " Text:"+note->getText()+"\n";
    return str;
}

QString TextExport::exportBinary(QString name,Binary* note,unsigned int titleLevel)
{
    QString str = base(name,note,titleLevel);
    str += " Path:"+note->getPath()+"\n";
    str += " Description:"+note->getDescription()+"\n";
    return str;
}
QString TextExport::exportImage(Image* note,unsigned int titleLevel)
{
    return exportBinary("Image",note,titleLevel);
}
QString TextExport::exportVideo(Video* note,unsigned int titleLevel)
{
    return exportBinary("Video",note,titleLevel);
}
QString TextExport::exportAudio(Audio* note,unsigned int titleLevel)
{
    return exportBinary("Audio",note,titleLevel);
}

QString TextExport::exportDocument(Document* note,unsigned int titleLevel)
{
    QString str = base("Document",note,titleLevel);
    str += " Notes: "
                  +QString::number(note->getNumberOfSubNotes())
                  +"\n";
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += indent(this->exportNote(note->getSubNote(i)));
    }
    return titleLevel ? indent(str) : str;
}
