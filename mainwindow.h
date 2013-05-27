#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>

#include "notesmanager.h"
#include "tagmanager.h"
#include "notewidget.h"
#include "articlewidget.h"
#include "documentwidget.h"
#include "imagewidget.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadNote(Note* n);
    static NoteWidget* makeWidget(Note* note, QWidget* parent=0);

public slots:
    void tabChanged(int i);
    void addNote(QAction* a);

private:
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    Ui::MainWindow *ui;
    NotesManager* nm;
    TagManager* tm;
    NoteWidget* currentNote;
};

#endif // MAINWINDOW2_H
