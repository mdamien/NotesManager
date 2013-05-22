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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void addNote(QAction* a);
    void ongletChanged(int);

    void displayView(QAction* a);

private :
    QVBoxLayout* layoutEditor, *layoutHTML, *layoutText, *layoutLatex;
    QScrollArea *areaEditor, *areaHTML, *areaLatex, *areaText;
    QTextEdit *textText, *textHTML, *textLatex;
    QTabWidget* onglets;
    QAction *aEditor, *aText, *aHTML, *aLatex, *aArticle, *aImage, *aVideo, *aAudio;
};

#endif // MAINWINDOW_H
