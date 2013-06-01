#include "notesmanager.h"
#include <ctime>
#include <QDebug>
#include "notesparser.h"
#include <QTime>

using namespace std;

NotesManager* NotesManager::notesManager = 0;

NotesManager::NotesManager()
{
    notes = new QSet<Note*>();
    strategies = ExportStrategy::getExportStrategies();
    trash = Trash::getInstance();
    receivedModif = false;
    history = new HistoryManager();
}

NotesManager::~NotesManager()
{
    //Il faut aussi penser à supprimer tous les pointeurs vers les Notes, donc on sauvegarde tout au moment du delete ?

    for(QSet<Note*>::Iterator it = notes->begin(); it != notes->end() ; it++)
    {
        delete(*it);
    }
    notes->clear();
    delete notes;
    notes = 0;

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
    }
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

ExportStrategy *NotesManager::getExporter(const QString& exporter)
{
    return strategies->at(exporter);
}

QString NotesManager::getPath() const
{
    return path;
}

void NotesManager::setPath(const QString& p)
{
    path = p;
}

void NotesManager::saveState()
{
    //A définir
}

void NotesManager::addRessource(Note* n)
{
    notes->insert(n);
}

void NotesManager::deleteRessource(Note* n)
{
 //   delete(*(notes->find(n))); //Supprime la Note en mémoire
    notes->remove(n);
}

void NotesManager::load()
{
    NotesParser().parseWorkplace();
}

void NotesManager::load(const QString& newPath)
{
    this->setPath(newPath);
    load();
}

void NotesManager::reset()
{
    notes->clear();
}

Note* NotesManager::loadNote(const unsigned int i)
{
    return NotesParser().parseNote(path,i);
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

unsigned int NotesManager::getNewId() //Renvoie un id unique en fonction de la date "actuelle"
{
    unsigned int id = 0;
    do
    {
        id = qrand() % 10000;
    }
    while(getNoteByID(id) != NULL);
    return id;
    //return std::time(0);
}

HistoryManager *NotesManager::getHistory()
{
    return history;
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

bool NotesManager::noteModified() const
{
    return receivedModif;
}

void NotesManager::setNoteModified(const bool& modif)
{
    receivedModif = modif;
}
