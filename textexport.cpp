#include "textexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>

TextExport::TextExport()
{
}

QString TextExport::base(QString name,Note* note,unsigned int n){
    return indent(name +":\n",n)
           +indent(" ID:"+QString::number(note->getId())+"\n",n)
           +indent(" Title:"+note->getTitle() + "\n",n);
}
QString TextExport::exportArticle(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note,titleLevel);
    str += indent(" Text:"+note->getText()+"\n",titleLevel);
    return str;
}

QString TextExport::exportBinary(QString name,Binary* note,unsigned int titleLevel)
{
    QString str = base(name,note,titleLevel);
    str += indent(" Path:"+note->getPath()+"\n",titleLevel);
    str += indent(" Description:"+note->getDescription()+"\n",titleLevel);
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
    str += indent(" Notes: "
                  +QString::number(note->getNumberOfSubNotes())
                  +"\n",titleLevel);
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += this->exportNote(note->getSubNote(i),titleLevel+1);
    }
    return str;
}

QString TextExport::indent(QString s,unsigned int titleLevel)
{
    return QString().fill(' ',titleLevel*4)+s;
}
