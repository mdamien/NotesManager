#ifndef HTMLEXPORT_H
#define HTMLEXPORT_H

#include  <QString>
#include "exportstrategy.h"

/*! \class HTMLExport
 * \brief Classe d'export de note en HTML
 */
class HTMLExport : public ExportStrategy
{
private:
    QString exportBinary(QString tag, Binary* note, unsigned int titleLevel=0);
    QString title(Note *n, unsigned int titleLevel);
public:
    HTMLExport();
protected:
    QString header(Note* note);
    QString footer(Note* note);

    QString exportArticle(Article* note,unsigned int titleLevel = 0);
    QString exportDocument(Document* note,unsigned int titleLevel = 0);
    QString exportImage(Image* note,unsigned int titleLevel=0);
    QString exportVideo(Video* note,unsigned int titleLevel=0);
    QString exportAudio(Audio* note, unsigned int titleLevel=0);
};


#endif // HTMLEXPORT_H
