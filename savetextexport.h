#ifndef SAVETEXTEXPORT_H
#define SAVETEXTEXPORT_H

#include "exportstrategy.h"

class SaveTextExport : public ExportStrategy
{
private:
    QString base(QString name, Note* note, unsigned int n);//base commune à chaque export
    QString exportBinary(QString name,Binary* note,unsigned int titleLevel=0);//helper pour les binaires
public:
    SaveTextExport();
protected:
    QString exportArticle(Article* note,unsigned int titleLevel = 0);
    QString exportDocument(Document* note,unsigned int titleLevel = 0);
    QString exportImage(Image* note,unsigned int titleLevel=0);
    QString exportVideo(Video* note,unsigned int titleLevel=0);
    QString exportAudio(Audio* note, unsigned int titleLevel=0);
};

#endif // SAVETEXTEXPORT_H