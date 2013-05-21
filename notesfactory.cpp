#include "articlefactory.h"

NotesFactory::NotesFactory()
{
}

unsigned int NotesFactory::getNewId() const //Renvoie un id unique en fonction de la date "actuelle"
{
    return std::time(0);
}

const std::map<QString, NotesFactory::NotesFactory*>& NotesFactory::getFactories()
{
    std::map<QString, NotesFactory*> factories;
    ArticleFactory* a = new ArticleFactory;
    factories[QString("Article")] = a;
    return factories;
}

