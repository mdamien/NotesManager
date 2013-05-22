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

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void addArticle()
    {
        ArticleWidget* a = new ArticleWidget("Titre", "Contenu", this);
        layoutEditor->addWidget(a);
    }

    void ongletChanged(int);

    void displayView(QAction* a)
    {
        if(a == aEditor)
        {
            onglets->setCurrentIndex(0);
        }
        else if(a == aText)
        {
            onglets->setCurrentIndex(1);
        }
        else if(a == aHTML)
        {
            onglets->setCurrentIndex(2);
        }
        else if(a == aLatex)
        {
            onglets->setCurrentIndex(3);
        }
    }

private :
    QVBoxLayout* layoutEditor, *layoutHTML, *layoutText, *layoutLatex;
    QScrollArea *areaEditor, *areaHTML, *areaLatex, *areaText;
    QTextEdit *textText, *textHTML, *textLatex;
    QTabWidget* onglets;
    QAction *aEditor, *aText, *aHTML, *aLatex;
};

#endif // MAINWINDOW_H
