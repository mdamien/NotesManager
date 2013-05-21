#include "exportstrategy.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include <typeinfo>
#include "textexport.h"
#include "htmlexport.h"

ExportStrategy::ExportStrategy()
{

}

QString ExportStrategy::exportNote(Note* note, unsigned int titleLevel)
{
    QString s = "";
    if(typeid(*note) == typeid(Article))
        s = exportArticle((Article*)note, titleLevel);
    else if(typeid(*note) == typeid(Document))
        s = exportDocument((Document*)note, titleLevel);
    else if(typeid(*note) == typeid(Audio))
        s = exportAudio((Audio*)note, titleLevel);
    else if(typeid(*note) == typeid(Video))
        s = exportVideo((Video*)note, titleLevel);
    else if(typeid(*note) == typeid(Image))
        s = exportImage((Image*)note, titleLevel);
    else
        return "ERROR:Note type not implemented yet";
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
    (*strategies)["TextExport"] = new TextExport;
    (*strategies)["HTMLExport"] = new HTMLExport;

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
