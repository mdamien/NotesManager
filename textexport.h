#ifndef TEXTEXPORT_H
#define TEXTEXPORT_H

#include  <QString>
#include "exportstrategy.h"

/*! \class TextExport
 * \brief Classe d'export de note en texte basique mais descriptif
 */
class TextExport : public ExportStrategy
{
private:
    QString base(QString name, Note* note, unsigned int n);//Base commune à chaque export
    QString exportBinary(QString name,Binary* note,unsigned int titleLevel=0);//Helper pour les binaires
public:
    TextExport();
protected:
    QString exportArticle(Article* note,unsigned int titleLevel = 0);
    QString exportDocument(Document* note,unsigned int titleLevel = 0);
    QString exportImage(Image* note,unsigned int titleLevel=0);
    QString exportVideo(Video* note,unsigned int titleLevel=0);
    QString exportAudio(Audio* note, unsigned int titleLevel=0);
};

#endif // TEXTEXPORT_H
