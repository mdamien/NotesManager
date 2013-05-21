#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include  <QString>
#include "note.h"
#include "binary.h"
#include "article.h"
#include "document.h"

class ExportStrategy
{
public:
    ExportStrategy();
    QString exportNote(Note* note,unsigned int titleLevel = 0);
protected:
    virtual QString exportArticle(Article* note,unsigned int titleLevel = 0) = 0;
    virtual QString exportDocument(Document* note,unsigned int titleLevel = 0) = 0;
    virtual QString exportImage(Image* note,unsigned int titleLevel=0) = 0;
    virtual QString exportVideo(Video* note,unsigned int titleLevel=0) = 0;
    virtual QString exportAudio(Audio* note, unsigned int titleLevel=0) = 0;
};

#endif // EXPORTSTRATEGY_H
