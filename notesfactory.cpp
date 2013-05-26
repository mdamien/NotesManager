#include "articlefactory.h"
#include "documentfactory.h"
#include "videofactory.h"
#include "imagefactory.h"
#include "audiofactory.h"

NotesFactory::NotesFactory()
{

}

unsigned int NotesFactory::getNewId()  //Renvoie un id unique en fonction de la date "actuelle"
{
    return std::time(0);
}

std::map<QString, NotesFactory*>* NotesFactory::getFactories()
{
    std::map<QString, NotesFactory*>* factories = new std::map<QString, NotesFactory*>;
    (*factories)[QString("Article")] = new ArticleFactory;
    (*factories)[QString("Document")] = new DocumentFactory;
    (*factories)[QString("Video")] = new VideoFactory;
    (*factories)[QString("Image")] = new ImageFactory;
    (*factories)[QString("Audio")] = new AudioFactory;

    return factories;
}

