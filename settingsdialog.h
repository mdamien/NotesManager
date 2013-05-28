#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include "notesmanager.h"


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    static QString workplace();
    static bool binaryCopy();

public slots:
    void chooseWorkplace();
    void saveSettings();
    
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
