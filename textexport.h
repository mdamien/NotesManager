#ifndef TEXTEXPORT_H
#define TEXTEXPORT_H

#include  <QString>

#include "exportstrategy.h"

class Note;
class Article;
class Document;

class TextExport : public ExportStrategy
{
private:
    QString base(QString name,Note* note);//base commune à chaque export
public:
    TextExport();
    QString exportNote(Note* note,unsigned int titleLevel = 0);
    QString exportNote(Article* note,unsigned int titleLevel = 0);
    QString exportNote(Document* note,unsigned int titleLevel = 0);
};

#endif // TEXTEXPORT_H
