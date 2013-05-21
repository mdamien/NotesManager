#include "videofactory.h"

VideoFactory::VideoFactory()
{

}

Note* VideoFactory::buildNote(const unsigned int id, const QString& title, const QString& desc, const QString& path) const       //Mettre plutôt desc et path par défaut à "" ? ça permettrait de créer une note avec juste son id et son titre, après on ajoute son contenu si on veut
{
    return new Video(id, title, desc, path);
}

Note* VideoFactory::buildNewNote(const QString& title, const QString& desc, const QString& path) const
{
    return new Video(getNewId(), title, desc, path);
}

Note* VideoFactory::buildNoteCopy(Note* note) const
{
    if(note = dynamic_cast<Video*> (note))    //Ne pas copier quelque chose qui n'est pas une Video
      return new Video((Video*) note);

    return 0;
}
