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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    static MainWindow* getInstance(QWidget *parent = 0);
    static void deleteInstance();
    void addNoteWidget(Note* n);

    void loadNote(NoteWidget* n);
    static NoteWidget* makeWidget(Note* note, QWidget* parent=0);

public slots:
    void tabChanged(int i);
    void addNote(QAction* a);
    void loadSidebarNote(QListWidgetItem* item);

private:
    //MainWindow est un Singleton : pas de copie autorisée ni de création pour l'utilisateur
    explicit MainWindow(QWidget *parent = 0);
    MainWindow& operator=(const MainWindow&);
    MainWindow(const MainWindow&);
    ~MainWindow();

    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    void updateNotesList();

    Ui::MainWindow *ui;
    NotesManager* nm;
    TagManager* tm;
    NoteWidget* currentNote;

    static MainWindow* mw;
};

class NoteListItem : public QListWidgetItem{
public:
    NoteListItem(QString title,Note* note):QListWidgetItem(title),note(note){}
    Note* getNote(){return note;}
private:
    Note* note;
};

#endif // MAINWINDOW2_H
