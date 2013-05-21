#include "htmlexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>

HTMLExport::HTMLExport()
{
}

QString HTMLExport::exportArticle(Article* note,unsigned int titleLevel)
{
    return title(note,titleLevel)+"<p>"+note->getText().replace("\n","<br/>")+"<\p>\n";
}

QString HTMLExport::exportBinary(QString tag,Binary* note,unsigned int titleLevel)
{
    return title(note,titleLevel)+"<p>"+note->getDescription().replace("\n","<br/>")+"<\p>\n"
            +"<"+tag+" src='"+note->getPath()+"' alt='"+note->getDescription()+"' />\n";
}
QString HTMLExport::exportImage(Image* note,unsigned int titleLevel)
{
    return exportBinary("img",note,titleLevel);
}
QString HTMLExport::exportVideo(Video* note,unsigned int titleLevel)
{
    return exportBinary("video",note,titleLevel);
}
QString HTMLExport::exportAudio(Audio* note,unsigned int titleLevel)
{
    return exportBinary("audio",note,titleLevel);
}

QString HTMLExport::exportDocument(Document* note,unsigned int titleLevel)
{
    QString str = title(note,titleLevel);
    str += "<ul>\n";
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += "<li>\n"+indent(this->exportNote(note->getSubNote(i),titleLevel+1))
               +"</li>\n";
    }
    str += "</ul>\n<br/>\n";
    return indent(str);
}

//ajoute un niveau d'indentation a chaque ligne
QString HTMLExport::indent(QString s)
{
    QString i = "    ";
    s.insert(0,i);
    int j = 0;
    while ((j = s.indexOf("\n", j)) != -1  && j < s.length()-1) {
        s.insert(j+1,i);
        ++j;
    }
    return s;
}

QString HTMLExport::title(Note* n,unsigned int titleLevel)
{
    return "<h"+QString::number(titleLevel+1)+">"+n->getTitle()
            +"</h"+QString::number(titleLevel+1)+">\n"; // add ID to make links ?
}

QString HTMLExport::header(Note* note)
{
    return "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "<meta charset=utf-8 />\n"
            "<title>"+note->getTitle()+"</title>\n"
            "</head>\n"
            "<body>\n";
}

QString HTMLExport::footer(Note* note)
{
    return "</body>\n"
           "</html>\n";
}
