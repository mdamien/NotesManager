#ifndef TEXTEXPORT_H
#define TEXTEXPORT_H

#include  <QString>
#include "exportstrategy.h"

class TextExport : public ExportStrategy
{
private:
    QString base(QString name, Note* note, unsigned int n);//base commune à chaque export
    QString indent(QString s,unsigned int size);//helper pour indenter
    QString exportBinary(QString name,Binary* note,unsigned int titleLevel=0);//helper pour les binaires
public:
    TextExport();
    QString exportNote(Note* note,unsigned int titleLevel = 0);
    QString exportNote(Article* note,unsigned int titleLevel = 0);
    QString exportNote(Document* note,unsigned int titleLevel = 0);
    QString exportNote(Image* note,unsigned int titleLevel=0);
    QString exportNote(Video* note,unsigned int titleLevel=0);
    QString exportNote(Audio* note, unsigned int titleLevel=0);
};

#endif // TEXTEXPORT_H
