#include "exportstrategy.h"
#include "note.h"
#include "article.h"
#include "document.h"
#include "binary.h"
#include <typeinfo>

ExportStrategy::ExportStrategy()
{
}


QString ExportStrategy::exportNote(Note* note,unsigned int titleLevel)
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
        return "ERROR:Note type not yet implemented";
    if(titleLevel == 0){
        s = header() + s + footer();
    }
    return s;
}
QString ExportStrategy::header()
{
    return "";
}
QString ExportStrategy::footer()
{
    return "";
}
