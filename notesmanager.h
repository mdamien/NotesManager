#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "note.h"
#include "notesfactory.h"
#include "exportstrategy.h"
#include <QSet>
#include <map>
#include "textexport.h"
#include "htmlexport.h"
#include "mainwindow.h"

class NotesManager
{
public:
    static NotesManager* getInstance();
    static void deleteInstance();
    QString getPath() const;
    void setPath(const QString& p);
    Note* getNote(const unsigned int i);
    void saveState();
    void addRessource(Note* n);
    void deleteRessource(Note* n);
    QString getFileName(const unsigned int i) const;
    void load();
    void load(const QString& newPath);
    void reset();
    void loadNote(const unsigned int i);
    std::map<QString, ExportStrategy*>* getExporter();

    Note* getNoteByID(unsigned int id);

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
    std::map<QString, NotesFactory*>* factories;
    std::map<QString, ExportStrategy*>* strategies;
};

#endif // NOTESMANAGER_H
