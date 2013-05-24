#ifndef AUDIOFACTORY_H
#define AUDIOFACTORY_H

#include "notesfactory.h"

class AudioFactory : public NotesFactory
{
public:
    AudioFactory();
    Note* buildNote(const unsigned int id, const QString& title, const QString& desc, const QString& path) const;
    Note* buildNewNote(const QString& title, const QString& desc, const QString& path) const;
    Note* buildNoteCopy(Note* note) const;
    Note* buildNote(const unsigned int id, const QString& title) const;
    Note* buildNewNote(const QString& title) const;
};

#endif // AUDIOFACTORY_H
