#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "note.h"
#include "articlewidget.h"
#include <QScrollArea>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFrame>
#include <QTabWidget>
#include "notesmanager.h"
#include "textexport.h"
#include "htmlexport.h"
#include "audiowidget.h"
#include "videowidget.h"
#include <typeinfo>
#include <QListWidget>
#include <QInputDialog>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static MainWindow* getInstance(QWidget *parent = 0);
    static void deleteInstance();
    void addNoteWidget(Note* n);

signals:
    
public slots:
    void addNote(QAction* a);
    void ongletChanged(int);

    void displayView(QAction* a);
    void changeNoteTitle();
    void changeNote() {}
    void closeNote();


private :
    //MainWindow est un Singleton : pas de copie autorisée ni de création pour l'utilisateur
    explicit MainWindow(QWidget *parent = 0);
    MainWindow& operator=(const MainWindow&);
    MainWindow(const MainWindow&);
    ~MainWindow();

    QVBoxLayout* layoutEditor, *layoutHTML, *layoutText, *layoutLatex;
    QScrollArea *areaEditor, *areaHTML, *areaLatex, *areaText;
    QTextEdit *textText, *textHTML, *textLatex;
    QTabWidget* onglets;
    QAction *aEditor, *aText, *aHTML, *aLatex, *aArticle, *aImage, *aVideo, *aAudio;
    QListWidget* notesList;
    QLineEdit* noteTitleEdit;
    static MainWindow* mw;

    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
