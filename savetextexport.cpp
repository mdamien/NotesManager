#include "savetextexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>

SaveTextExport::SaveTextExport()
{
}

QString SaveTextExport::base(QString name,Note* note,unsigned int n){
    return name.toUpper()+"\n"+note->getTitle()+"\n";
}
QString SaveTextExport::exportArticle(Article* note,unsigned int titleLevel)
{
    QString str = base("Article",note,titleLevel);
    str += note->getText()+"\n";
    return str;
}

QString SaveTextExport::exportBinary(QString name,Binary* note,unsigned int titleLevel)
{
    QString str = base(name,note,titleLevel);
    str += note->getPath()+"\n";
    str += note->getDescription()+"\n";
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

QString SaveTextExport::exportDocument(Document* note,unsigned int titleLevel)
{
    QString str = base("Document",note,titleLevel);
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += QString::number(note->getSubNote(i)->getId())+"\n"; //ce sera a la fonction d'export, de bien exporter les sous-notes
    }
    return str;
}