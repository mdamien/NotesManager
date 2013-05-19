#ifndef TEXTEXPORT_H
#define TEXTEXPORT_H

#include  <QString>

#include "exportstrategy.h"

class Note;
class Article;

class TextExport : public ExportStrategy
{
public:
    TextExport();
    QString exportNote(Note* note,unsigned int titleLevel = 0);

};

#endif // TEXTEXPORT_H
