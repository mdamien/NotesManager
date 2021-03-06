#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "notesmanager.h"
#include "tagmanager.h"
#include "notewidget.h"
#include "articlewidget.h"
#include "documentwidget.h"
#include "imagewidget.h"
#include "binary.h"
#include "audiowidget.h"
#include "videowidget.h"
#include "settingsdialog.h"
#include <typeinfo>
#include <QMessageBox>
#include "trash.h"

/*! \namespace Ui
 *  \brief Espace de nom pour l'interface générée par le .ui
 */
namespace Ui {
class MainWindow;
}

/*! \class MainWindow
 * \brief Fenetre principale du programme
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    static MainWindow* getInstance(QWidget *parent = 0);
    static void deleteInstance();
    void addNoteWidget(Note* n);
    void closeCurrentNote();
    void loadNote(NoteWidget* n);
    NoteWidget* makeWidget(Note* note, QWidget* parent=0);
    void removeTextFromTabs();
    void updateTagFilter();

public slots:
    void tabChanged(int i);
    void addNote(QAction* a);
    void loadSidebarNote(QListWidgetItem* item);
    void updateNotesList();
    void updateTagsList();
    void updateTag(QListWidgetItem* item);
    void tagSearch();
    void addTag();
    void removeTag();
    void newNote();
    void save();
    void closeNote();
    void chooseNoteToOpen();
    void openSettings();
    void deleteWidget(NoteWidget* nw);
    void displayView(QAction* a);
    void closeEvent(QCloseEvent *);
    void saveHTML();
    void saveLatex();
    void filterNotesList(int);
    void addFilter(QListWidgetItem*);
    void undo();
    void redo();
    void toogleShowHTMLSource();
    void showAbout();
    void showHelp();

private:
    //MainWindow est un Singleton : pas de copie autorisée ni de création pour l'utilisateur
    explicit MainWindow(QWidget *parent = 0);
    MainWindow& operator=(const MainWindow&);
    MainWindow(const MainWindow&);
    ~MainWindow();

    //Méthode privée
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    //Attributs
    Ui::MainWindow *ui;
    NotesManager* nm;
    TagManager* tm;
    NoteWidget* currentNote;
    Trash* trash;
    static MainWindow* mw;
    QSet<QListWidgetItem*>* checkedTags;
    QSet<Note*>* filteredNotes;
};

// Classes utilisées pour faciliter la synchronisation entre les tags et l'interface
class TagListItem : public QListWidgetItem{
public:
    TagListItem(QString title,Tag* note):QListWidgetItem(title),tag(note){}
    Tag* getTag(){return tag;}

private:
    Tag* tag;
};

class NoteListItem : public QListWidgetItem{
public:
    NoteListItem(QString title,Note* note):QListWidgetItem(title),note(note){}
    Note* getNote(){return note;}

private:
    Note* note;
};

#endif // MAINWINDOW2_H
