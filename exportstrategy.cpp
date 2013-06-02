#include "exportstrategy.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include <typeinfo>
#include "textexport.h"
#include "htmlexport.h"
#include "latexexport.h"
#include "savetextexport.h"

ExportStrategy::ExportStrategy()
{

}

QString ExportStrategy::exportNote(Note* note, unsigned int titleLevel)
{
    QString s = "";
    QString name = typeid(*note).name();
    if(name == typeid(Article).name())
        s = exportArticle((Article*)note, titleLevel);
    else if(name == typeid(Document).name())
        s = exportDocument((Document*)note, titleLevel);
    else if(name == typeid(Audio).name())
        s = exportAudio((Audio*)note, titleLevel);
    else if(name == typeid(Video).name())
        s = exportVideo((Video*)note, titleLevel);
    else if(name == typeid(Image).name())
        s = exportImage((Image*)note, titleLevel);
    else
        return QString("ERROR:Note type ")+name+" not implemented yet";
    if(titleLevel == 0)
    {
        s = header(note) + s + footer(note);
    }

    return s;
}

QString ExportStrategy::header(Note* note)
{
    return "";
}

QString ExportStrategy::footer(Note* note)
{
    return "";
}

std::map<QString, ExportStrategy*>* ExportStrategy::getExportStrategies()
{
    std::map<QString, ExportStrategy*>* strategies = new std::map<QString, ExportStrategy*>;
    (*strategies)["Text"] = new TextExport;
    (*strategies)["HTML"] = new HTMLExport;
    (*strategies)["SaveText"] = new SaveTextExport;
    (*strategies)["LaTeX"] = new LaTeXExport;
    return strategies;
}

//ajoute un niveau d'indentation a chaque ligne
QString ExportStrategy::indent(QString s)
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
