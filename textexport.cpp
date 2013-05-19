#include "textexport.h"
#include "note.h"
#include "article.h"
#include "document.h"

TextExport::TextExport()
{
}

QString TextExport::base(QString name,Note* note){
    return name +":\n  ID:"+QString::number(note->getId())+"\n  Title:"+note->getTitle() + "\n";
}

QString TextExport::exportNote(Note* note,unsigned int titleLevel)
{
    return base("Note",note);
}
QString TextExport::exportNote(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note);
    str += "  Text:"+note->getText()+"\n";
    return str;
}
QString TextExport::exportNote(Document* note,unsigned int titleLevel)
{
    QString str = base("Document",note);
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += this->exportNote(note->getSubNote(i),titleLevel+1);
    }
    return str;
}
