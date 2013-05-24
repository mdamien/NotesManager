#include "audiofactory.h"

AudioFactory::AudioFactory()
{

}

Note* AudioFactory::buildNote(const unsigned int id, const QString& title, const QString& desc, const QString& path) const       //Mettre plutôt desc et path par défaut à "" ? ça permettrait de créer une note avec juste son id et son titre, après on ajoute son contenu si on veut
{
    return new Audio(id, title, desc, path);
}

Note* AudioFactory::buildNewNote(const QString& title, const QString& desc, const QString& path) const
{
    return new Audio(getNewId(), title, desc, path);
}

Note* AudioFactory::buildNoteCopy(Note* note) const
{
    if(note = dynamic_cast<Audio*> (note))    //Ne pas copier quelque chose qui n'est pas une note Audio
      return new Audio((Audio*) note);

    return 0;
}

Note* AudioFactory::buildNote(const unsigned int id, const QString& title) const
{
    return new Audio(id, title);
}

Note* AudioFactory::buildNewNote(const QString& title) const
{
    return new Audio(getNewId(), title);
}
