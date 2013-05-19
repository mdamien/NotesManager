#include "notesfactory.h"

NotesFactory::NotesFactory()
{
    //A définir peut être
}

unsigned int NotesFactory::getNewId() const //Renvoie un id unique en fonction de la date "actuelle"
{
    return std::time(0);
}

static map<QString, NoteFactory*>* getFactories()
{
    //A définir
    return 0;
}
