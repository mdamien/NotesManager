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

    virtual QString exportNote(Note* note,unsigned int titleLevel = 0) = 0;
};

#endif // EXPORTSTRATEGY_H
