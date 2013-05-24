#include "imagefactory.h"

ImageFactory::ImageFactory()
{

}

Note* ImageFactory::buildNote(const unsigned int id, const QString& title, const QString& desc, const QString& path) const       //Mettre plutôt desc et path par défaut à "" ? ça permettrait de créer une note avec juste son id et son titre, après on ajoute son contenu si on veut
{
    return new Image(id, title, desc, path);
}

Note* ImageFactory::buildNewNote(const QString& title, const QString& desc, const QString& path) const
{
    return new Image(getNewId(), title, desc, path);
}

Note* ImageFactory::buildNoteCopy(Note* note) const
{
    if(note = dynamic_cast<Image*> (note))    //Ne pas copier quelque chose qui n'est pas une Image
      return new Image((Image*) note);

    return 0;
}

Note* ImageFactory::buildNote(const unsigned int id, const QString& title) const
{
    return new Image(id, title);
}

Note* ImageFactory::buildNewNote(const QString& title) const
{
    return new Image(getNewId(), title);
}

