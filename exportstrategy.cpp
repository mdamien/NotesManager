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
    if(typeid(*note) == typeid(Article))
        return exportArticle((Article*)note, titleLevel);
    if(typeid(*note) == typeid(Document))
        return exportDocument((Document*)note, titleLevel);
    if(typeid(*note) == typeid(Audio))
        return exportAudio((Audio*)note, titleLevel);
    if(typeid(*note) == typeid(Video))
        return exportVideo((Video*)note, titleLevel);
    if(typeid(*note) == typeid(Image))
        return exportImage((Image*)note, titleLevel);

    return "ERROR:Note type not yet implemented";
}
