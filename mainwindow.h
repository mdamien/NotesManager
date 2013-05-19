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
        a->setMinimumSize(500, 150);
        vLayout->addWidget(a);

        setCentralWidget(sa);
    }

private :
    QVBoxLayout* vLayout;
    QScrollArea* sa;
    QFrame* container;
};

#endif // MAINWINDOW_H
