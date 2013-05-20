#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QList>
#include <QApplication>

class ExportStrategy;

class Note
{
public:
    unsigned int getId() const;
    QString getTitle() const;
    void setTitle(const QString& title);
    bool isModified() const;
    virtual QString exportNote(ExportStrategy* es) const { return "fuck";}; // a mettre
    //QString exportAsPart(ExportStrategy* es) const;
    //void addSudNote(Note* n);    //Devrait être UNIQUEMENT dans Document, à vérifier
    //void removeSubNote(const unsigned int i);  //Devrait être UNIQUEMENT dans Document, à vérifier

protected :
    Note(const unsigned int id, const QString& title = "");
    virtual void load() = 0; //Chargement différent en fonction du type de fichier
    unsigned int id;
    QString title;
    bool modified;
    bool loaded;
};

#endif // NOTE_H
