#include "notesmanager.h"

#include <QDebug>

using namespace std;

NotesManager* NotesManager::notesManager = 0;

NotesManager::NotesManager()
{
    notes = new QSet<Note*>();
    factories = NotesFactory::getFactories();
    strategies = ExportStrategy::getExportStrategies();
}

NotesManager::~NotesManager()
{
    //Il faut aussi penser à supprimer tous les pointeurs vers les Notes, donc on sauvegarde tout au moment du delete ?

    for(QSet<Note*>::Iterator it = notes->begin(); it != notes->end() ; it++)
    {
        notes->erase(it); //Je vois que ça, je sais pas si ça delete le pointeur...
    }
    notes->clear();
    delete notes;
    notes = 0;

    //Suppression de la map contenant les Factories
    for(std::map<QString, NotesFactory*>::iterator it = factories->begin(); it != factories->end(); it++)
    {
        delete it->second;
    }
    delete factories;
    factories = 0;

    //Suppression de la map contenant les Strategies
    for(std::map<QString, ExportStrategy*>::iterator it = strategies->begin(); it != strategies->end(); it++)
    {
        delete it->second;
    }
    delete strategies;
    strategies = 0;
}

NotesManager* NotesManager::getInstance()
{
    if(!notesManager)
    {
        notesManager = new NotesManager;
        return notesManager;
    }
    else
        return notesManager;
}

void NotesManager::deleteInstance()
{
    if(notesManager)
    {
        delete notesManager;
        notesManager = 0;     //Remise du pointeur à 0
    }
}

std::map<QString, ExportStrategy*>* NotesManager::getExporter()
{
    return strategies;
}

QString NotesManager::getPath() const
{
    return path;
}

void NotesManager::setPath(const QString& p)
{
    path = p;
}

Note* NotesManager::getNote(const unsigned int i)
{
    return 0;
}

void NotesManager::saveState()
{
    //A définir
}

void NotesManager::addRessource(Note* n)
{
    qDebug() << "Ressource added:" << n->getId() << n->getTitle();
    notes->insert(n);
}

void NotesManager::deleteRessource(Note* n)
{
    notes->remove(n);
}

QString NotesManager::getFileName(const unsigned int i) const
{
    //A définir : ajouter un filename à chaque Note, non ?
    return "";
}

void NotesManager::load()
{
    NotesManager* nm = NotesManager::getInstance();
    MainWindow* mw = MainWindow::getInstance();

    for(NotesManager::Iterator it = nm->begin(); it != nm->end(); ++it)
    {
        if((*it)->isLoaded())
            mw->addNoteWidget(*it);
    }
}

void NotesManager::load(const QString& newPath)
{
    //A définir
}

void NotesManager::reset()
{
    //A définir
}

void NotesManager::loadNote(const unsigned int i)
{
    //A définir
}

Note* NotesManager::getNoteByID(unsigned int id)
{
    for(Iterator it = begin();it != end();++it)
    {
        if ((*it)->getId() == id)
        {
            return (*it);
        }
    }
    return NULL;
}

//Iterator sur le contenu de NotesManager

NotesManager::Iterator NotesManager::begin()
{
    return Iterator(notes->begin());
}

NotesManager::Iterator NotesManager::end()
{
    return Iterator(notes->end());
}

NotesManager::Iterator::Iterator(const QSet<Note*>::Iterator& it)
{
    itNotes = it;
}

NotesManager::Iterator& NotesManager::Iterator::operator++()
{
    itNotes++;
}

NotesManager::Iterator& NotesManager::Iterator::operator--()
{
    itNotes--;
}

Note* NotesManager::Iterator::operator*()
{
    return *itNotes;
}

bool NotesManager::Iterator::operator==(const Iterator& it) const
{
    return itNotes == it.itNotes;
}

bool NotesManager::Iterator::operator!=(const Iterator& it) const
{
    return itNotes != it.itNotes;
}

std::map<QString, NotesFactory*>* NotesManager::getFactory()
{
    return factories;
}
