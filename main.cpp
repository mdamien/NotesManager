#include <QApplication>

#include "mainwindow.h"
#include "notesmanager.h"
#include "settingsdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Notes Manager");
    NotesManager* nm = NotesManager::getInstance();
    nm->load(SettingsDialog::workplace());
    MainWindow* m = MainWindow::getInstance();
    m->show();
    return app.exec();
}
