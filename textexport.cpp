#include "textexport.h"
#include "note.h"
#include "article.h"
#include "document.h"

TextExport::TextExport()
{
}

QString TextExport::base(QString name,Note* note,unsigned int n){
    return indent(name +":\n",n)
           +indent(" ID:"+QString::number(note->getId())+"\n",n)
           +indent(" Title:"+note->getTitle() + "\n",n);
}

QString TextExport::exportNote(Note* note,unsigned int titleLevel)
{
    return base("Note",note,titleLevel);
}
QString TextExport::exportNote(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note,titleLevel);
    str += indent(" Text:"+note->getText()+"\n",titleLevel);
    return str;
}
QString TextExport::exportNote(Document* note,unsigned int titleLevel)
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
