#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H

#include  <QString>

class Note;

class ExportStrategy
{
public:
    ExportStrategy();
    QString exportNote(Note* note,unsigned int titleLevel = 0); //virtual normalement
};

#endif // EXPORTSTRATEGY_H
