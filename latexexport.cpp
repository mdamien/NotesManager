#include "latexexport.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include <typeinfo>

LaTeXExport::LaTeXExport()
{
}

QString LaTeXExport::exportArticle(Article* note,unsigned int titleLevel)
{
    QString s = section(note,titleLevel)
            +"\\paragraph{}"+note->getText()+"\n\n";
    return s;
}

QString LaTeXExport::exportBinary(QString tag,Binary* note,unsigned int titleLevel)
{
    QString s = section(note,titleLevel)+"<p>"+note->getDescription().replace("\n","<br/>")+"<\p>\n"
            +"<"+tag+" src='"+note->getPath()+"' alt='"+note->getDescription()+"' />\n";
    return titleLevel == 0 ? indent(s) : s;
}
QString LaTeXExport::exportImage(Image* note,unsigned int titleLevel)
{
    return section(note,titleLevel)
            + "\\begin{center}\n"
            + "\\includegraphics{"+note->getPath()+"}\n"
            +"\\paragraph{}"+note->getDescription()+"\n"
            +"\\end{center}\n\n";
}
QString LaTeXExport::exportVideo(Video* note,unsigned int titleLevel)
{
    return exportBinary("video",note,titleLevel);
}
QString LaTeXExport::exportAudio(Audio* note,unsigned int titleLevel)
{
    return exportBinary("audio",note,titleLevel);
}

QString LaTeXExport::exportDocument(Document* note,unsigned int titleLevel)
{
    QString str = section(note,titleLevel)+"\n";
    for(unsigned int i=0;i < note->getNumberOfSubNotes();i++){
       str += this->exportNote(note->getSubNote(i),titleLevel+1);
    }
    return str;
}

QString LaTeXExport::section(Note* n,unsigned int titleLevel)
{
    QString str = "\\";
    switch (titleLevel) {
    case 0:
        str += "chapter";
        break;
    case 1:
        str += "section";
        break;
    case 2:
        str += "subsection";
        break;
    default:
        str += "subsubsection";
        break;
    }
    return str+ "{"+n->getTitle()+"}\n";
}

QString LaTeXExport::header(Note* note)
{
    return "\\documentclass[a4paper,11pt]{report}\n"
            "\\usepackage{graphicx}\n"
            "\\usepackage[francais]{babel}\n"
            "\\usepackage[latin1]{inputenc}\n"
            "\\usepackage[T1]{fontenc}\n"
            "\\begin{document}\n";
}
QString LaTeXExport::footer(Note* note)
{
    return "\\end{document}\n";
}
