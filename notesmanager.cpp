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

/*!
 * \brief Renvoie un exporter du type demandé
 * \param exporter : Chaîne de caractère utilisée pour choisir le type d'exporter demandé(Text, HTML, LaTeX)
 * \return
 */
ExportStrategy *NotesManager::getExporter(const QString& exporter)
{
    return strategies->at(exporter);
}

/*!
 * \brief Renvoie l'emplacement du workspace
 * \return
 */
QString NotesManager::getPath() const
{
    return path;
}

/*!
 * \brief Définit l'emplacement du workspace
 * \param p : Chemin du workspace
 */
void NotesManager::setPath(const QString& p)
{
    path = p;
}

/*!
 * \brief Ajoute une note au set de notes géré par le NotesManager
 * \param n : Note à ajouter
 */
void NotesManager::addRessource(Note* n)
{
    notes->insert(n);
}

/*!
 * \brief Supprime la note : du set du NotesManager, mais aussi du disque dur.
 * \param n : Note à supprimer
 */
void NotesManager::deleteRessource(Note* n)
{
    n->setLoaded(false);
    QFile::remove(QString(n->getId()));
    delete(*(notes->find(n))); //Supprime la Note en mémoire
    notes->remove(n);
}

/*!
 * \brief Charge le NotesManager
 */
void NotesManager::load()
{
    NotesParser().parseWorkplace();
}

/*!
 * \brief Charge le NotesManager à partir d'un emplacement précis et redéfinit l'emplacement du NotesManager
 * \param newPath : Emplacement du NotesManager à définir
 */
void NotesManager::load(const QString& newPath)
{
    this->setPath(newPath);
    load();
}

/*!
 * \brief Vide le set de notes du NotesManager sans libérer la mémoire
 */
void NotesManager::reset()
{
    notes->clear();
}

Note* NotesManager::loadNote(const unsigned int i)
{
    return NotesParser().parseNote(path,i);
}

/*!
 * \brief Renvoie une note présente dans le set du NotesManager en fonction d'un ID donné
 * \param id : Identifiant de la note à rechercher
 * \return Retourne la note chargée
 */
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

/*!
 * \brief  Renvoie un id unique en utilisant une fonction de génération de nombre aléatoire. Vérifie qu'il n'existe pas déjà un tel identifiant.
 * \return Un identifiant unique pour une note.
 */
unsigned int NotesManager::getNewId()
{
    unsigned int id = 0;
    do
    {
        id = qrand() % 10000;
    }
    while(getNoteByID(id) != NULL);
    return id;
}

/*!
 * \brief Renvoie l'historique géré par le NotesManager
 * \return Historique géré par le NotesManager.
 */
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
