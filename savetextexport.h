#ifndef SAVETEXTEXPORT_H
#define SAVETEXTEXPORT_H

#include "exportstrategy.h"

/*! \class SaveTextExport
 * \brief Classe permettant d'exporter dans le format de sauvegarde sur disque
 */
class SaveTextExport : public ExportStrategy
{
private:
    QString base(QString name, Note* note, unsigned int n);//Base commune à chaque export
    QString exportBinary(QString name,Binary* note,unsigned int titleLevel=0);//Helper pour les binaires

public:
    SaveTextExport();

    QString exportTagsMetafile();
    QString exportNotesMetafile();

    static void save();
protected:
    QString exportArticle(Article* note,unsigned int titleLevel = 0);
    QString exportDocument(Document* note,unsigned int titleLevel = 0);
    QString exportImage(Image* note,unsigned int titleLevel=0);
    QString exportVideo(Video* note,unsigned int titleLevel=0);
    QString exportAudio(Audio* note, unsigned int titleLevel=0);

    static void writeToFile(QString path,QString content);
};

#endif // SAVETEXTEXPORT_H
