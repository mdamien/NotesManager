#ifndef HTMLEXPORT_H
#define HTMLEXPORT_H

#include  <QString>
#include "exportstrategy.h"

class HTMLExport : public ExportStrategy
{
private:
    QString base(QString name, Note* note, unsigned int n);
    QString exportBinary(QString name,Binary* note,unsigned int titleLevel=0);
    QString indent(QString s,unsigned int titleLevel);
public:
    HTMLExport();
protected:
    QString header();
    QString footer();

    QString exportArticle(Article* note,unsigned int titleLevel = 0);
    QString exportDocument(Document* note,unsigned int titleLevel = 0);
    QString exportImage(Image* note,unsigned int titleLevel=0);
    QString exportVideo(Video* note,unsigned int titleLevel=0);
    QString exportAudio(Audio* note, unsigned int titleLevel=0);
};


#endif // HTMLEXPORT_H
