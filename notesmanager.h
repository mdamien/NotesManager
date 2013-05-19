#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "note.h"
#include <QSet>
#include <QMap>

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
//    ExportStrategy* getExporter();

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
//    QMap<QString, NotesFactory>* factories;
//    QMap<QString, ExportStrategy*>* strategies;
};

#endif // NOTESMANAGER_H
