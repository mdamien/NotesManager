#ifndef VIDEOFACTORY_H
#define VIDEOFACTORY_H

#include "notesfactory.h"

class VideoFactory : public NotesFactory
{
public:
    VideoFactory();
    Note* buildNote(const unsigned int id, const QString& title, const QString& desc, const QString& path) const;
    Note* buildNewNote(const QString& title, const QString& desc, const QString& path) const;
    Note* buildNoteCopy(Note* note) const;
};

#endif // VIDEOFACTORY_H
