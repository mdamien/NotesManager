#ifndef LATEXEXPORT_H
#define LATEXEXPORT_H

#include  <QString>
#include "exportstrategy.h"

/*! \class LaTeXExport
 * \brief Classe d'export de note en LaTeX
 */
class LaTeXExport : public ExportStrategy
{
private:
    QString section(Note *n, unsigned int titleLevel);
public:
    LaTeXExport();
protected:
    QString header(Note* note);
    QString footer(Note* note);

    QString exportArticle(Article* note,unsigned int titleLevel = 0);
    QString exportDocument(Document* note,unsigned int titleLevel = 0);
    QString exportImage(Image* note,unsigned int titleLevel=0);
    QString exportVideo(Video* note,unsigned int titleLevel=0);
    QString exportAudio(Audio* note, unsigned int titleLevel=0);
};

#endif // LATEXEXPORT_H
