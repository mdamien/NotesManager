#include "textexport.h"
#include "note.h"
#include "article.h"

TextExport::TextExport()
{
}

QString TextExport::exportNote(Note* note,unsigned int titleLevel)
{
    note->getTitle();
    return "Yo ma poule! Ca marche! 2";
}

