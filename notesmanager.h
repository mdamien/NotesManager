#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "note.h"
#include "exportstrategy.h"
#include <QSet>
#include <map>
#include "textexport.h"
#include "htmlexport.h"
#include "trash.h"
#include "historymanager.h"

class NotesManager
{
public:
    static NotesManager* getInstance();
    static void deleteInstance();
    QString getPath() const;
    void setPath(const QString& p);
    void addRessource(Note* n);
    void deleteRessource(Note* n);
    void load();
    void load(const QString& newPath);
    void reset();
    Note* loadNote(const unsigned int i);
    ExportStrategy* getExporter(const QString& exporter);
    Note* getNoteByID(const unsigned int id);
    bool noteModified() const;
    void setNoteModified(const bool& modif = true);
    unsigned int getNewId();
    HistoryManager* getHistory();

    //Iterator
    class Iterator
    {
        friend class NotesManager; //Pour accéder au constructeur de l'Iterator
    public :
        Iterator& operator++();
        Iterator& operator--();
        Note* operator*();
        bool operator==(const Iterator& it) const;
        bool operator!=(const Iterator& it) const;
    private :
        Iterator(const QSet<Note*>::Iterator& it);
        QSet<Note*>::Iterator itNotes;
    };

    Iterator begin();
    Iterator end();

private:
    //Implémentation du design pattern Singleton
    NotesManager();
    NotesManager(const NotesManager&);
    NotesManager& operator=(const NotesManager&);
    ~NotesManager();

    //Attributs
    static NotesManager* notesManager;
    QSet<Note*>* notes; //Set pour ne pas avoir deux fois la même Note dans le NM
    QString path;
    std::map<QString, ExportStrategy*>* strategies;
    Trash* trash;
    bool receivedModif;
    HistoryManager* history;
};

#endif // NOTESMANAGER_H
