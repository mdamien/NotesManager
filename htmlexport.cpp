#include "htmlexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>

HTMLExport::HTMLExport()
{
}

QString HTMLExport::base(QString name,Note* note,unsigned int n){
    return indent(name +":\n",n)
           +indent(" ID:"+QString::number(note->getId())+"\n",n)
           +indent(" Title:"+note->getTitle() + "\n",n);
}
QString HTMLExport::exportArticle(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note,titleLevel);
    str += indent(" Text:"+note->getText()+"\n",titleLevel);
    str += indent("<br/>\n",titleLevel);
    return str;
}

QString HTMLExport::exportBinary(QString name,Binary* note,unsigned int titleLevel)
{
    QString str = base(name,note,titleLevel);
    str += indent(" Path:"+note->getPath()+"\n",titleLevel);
    str += indent(" Description:"+note->getDescription()+"\n",titleLevel);
    str += indent("<br/>\n",titleLevel);
    return str;
}
QString HTMLExport::exportImage(Image* note,unsigned int titleLevel)
{
    return exportBinary("Image",note,titleLevel);
}
QString HTMLExport::exportVideo(Video* note,unsigned int titleLevel)
{
    return exportBinary("Video",note,titleLevel);
}
QString HTMLExport::exportAudio(Audio* note,unsigned int titleLevel)
{
    return exportBinary("Audio",note,titleLevel);
}

QString HTMLExport::exportDocument(Document* note,unsigned int titleLevel)
{
    QString str = base("Document",note,titleLevel);
    str += indent(" Notes: "
                  +QString::number(note->getNumberOfSubNotes())
                  +"\n",titleLevel);
    str += indent("<ul>\n",titleLevel);
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += indent("<li>\n",titleLevel);
       str += this->exportNote(note->getSubNote(i),titleLevel+1);
       str += indent("</li>\n",titleLevel);
    }
    str += indent("</ul>\n",titleLevel);
    str += indent("<br/>\n",titleLevel);
    return str;
}

QString HTMLExport::indent(QString s,unsigned int titleLevel)
{
    return QString().fill(' ',titleLevel*4)+s;
}
QString HTMLExport::header()
{
    return "<body>\n";
}
QString HTMLExport::footer()
{
    return "</body>\n";
}
