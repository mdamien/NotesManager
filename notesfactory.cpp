#include "articlefactory.h"
#include "documentfactory.h"

NotesFactory::NotesFactory()
{

}

unsigned int NotesFactory::getNewId() const //Renvoie un id unique en fonction de la date "actuelle"
{
    return std::time(0);
}

std::map<QString, NotesFactory*>* NotesFactory::getFactories()
{
    std::map<QString, NotesFactory*>* factories = new std::map<QString, NotesFactory*>;
    (*factories)[QString("Article")] = new ArticleFactory;
    (*factories)[QString("Document")] = new DocumentFactory;

    return factories;
}

