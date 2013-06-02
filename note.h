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
    void setModified(const bool modified);
    QString exportNote(ExportStrategy* es) const;
    void setLoaded(const bool);
    bool isLoaded() const;

protected :
    Note(const unsigned int id, const QString& title = "");
    virtual void load() = 0; //Note est ainsi abstraite
    unsigned int id;
    QString title;
    bool modified;
    bool loaded;
};

#endif // NOTE_H
