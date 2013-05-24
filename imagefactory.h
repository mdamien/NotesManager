#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H

#include "notesfactory.h"

class ImageFactory : public NotesFactory
{
public:
    ImageFactory();
    Note* buildNote(const unsigned int id, const QString& title, const QString& desc, const QString& path) const;
    Note* buildNewNote(const QString& title, const QString& desc, const QString& path) const;
    Note* buildNoteCopy(Note* note) const;
    Note* buildNote(const unsigned int id, const QString& title) const;
    Note* buildNewNote(const QString& title) const;
};

#endif // IMAGEFACTORY_H
