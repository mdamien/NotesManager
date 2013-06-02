#ifndef TRASH_H
#define TRASH_H

#include <QWidget>
#include "note.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include "document.h"
#include <typeinfo>

class TrashedListItem;

class Trash : public QWidget
{
    Q_OBJECT
public:
    void addItem(Note* note, Document* parent = 0);
    static Trash* getInstance(QWidget *parent = 0);
    static void deleteInstance();

    //Iterator
    class Iterator
    {
        friend class Trash;
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

signals:
    
public slots:
    void showTrash();
    void deleteSelection();
    void restoreSelection();
    void addToSelection(QListWidgetItem* item);

private :
    QSet<Note*>* notes;
    QSet<QListWidgetItem*>* selection;
    QListWidget* notesList;

    //Implémentation du Singleton
    ~Trash();
    explicit Trash(QWidget *parent = 0);
    Trash(const Trash&);
    Trash& operator=(const Trash&);
    static Trash* trash;
};

//Héritages de QListWidgetItem pour permettre de retrouver facilement les notes sélectionnées
class TrashedListItem : public QListWidgetItem
{
public :
    TrashedListItem(Note* note) : QListWidgetItem(note->getTitle()), note(note) {}
    Note* getNote() { return note; }

private :
    Note* note;
};

class TrashedSubNoteListItem : public TrashedListItem
{
public :
    TrashedSubNoteListItem(Note* note, Document* parent) : TrashedListItem(note), parentNote(parent) {}
    Document* getParentDocument() { return parentNote; }
private :
    Document* parentNote;
};

#endif // TRASH_H
