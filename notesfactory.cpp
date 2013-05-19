#include "notesfactory.h"

NotesFactory::NotesFactory()
{
    //A définir peut être
}

unsigned int NotesFactory::getNewId() const //Renvoie un id unique en fonction de la date "actuelle"
{
    return std::time(0);
}

map<QString, NotesFactory::NoteFactory*>* NotesFactory::getFactories()
{
    //A définir
    return 0;
}
