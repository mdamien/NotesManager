#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include  <QString>
#include <map>
#include "note.h"
#include "binary.h"
#include "article.h"
#include "document.h"

/*! \class ExportStrategy
 * \brief Classe abstraite d'export de note
 */
class ExportStrategy
{
public:
    ExportStrategy();
    QString exportNote(Note* note,unsigned int titleLevel = 0);
    static std::map<QString, ExportStrategy*>* getExportStrategies();

protected:
    virtual QString header(Note* note);
    virtual QString footer(Note* note);

    virtual QString exportArticle(Article* note,unsigned int titleLevel = 0) = 0;
    virtual QString exportDocument(Document* note,unsigned int titleLevel = 0) = 0;
    virtual QString exportImage(Image* note,unsigned int titleLevel=0) = 0;
    virtual QString exportVideo(Video* note,unsigned int titleLevel=0) = 0;
    virtual QString exportAudio(Audio* note, unsigned int titleLevel=0) = 0;

    QString indent(QString s);
};

#endif // EXPORTSTRATEGY_H
