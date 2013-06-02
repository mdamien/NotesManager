#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->workplace_linedit->setText(workplace());
    ui->copy_binary->setChecked(binaryCopy());
    ui->proxy->setText(proxy());

    connect(ui->workplace_choose,SIGNAL(clicked()),this,SLOT(chooseWorkplace()));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(saveSettings()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::workplace()
{
    QSettings settings("lo21-maxetdam", "NotesManager");
    return settings.value("workplace","../notesmanager/workplace").toString();
}
QString SettingsDialog::proxy()
{
    QSettings settings("lo21-maxetdam", "NotesManager");
    return settings.value("proxy","").toString();
}

bool SettingsDialog::binaryCopy()
{
    QSettings settings("lo21-maxetdam", "NotesManager");
    return settings.value("binary_copy",false).toBool();
}

void SettingsDialog::chooseWorkplace()
{
    QString path = QFileDialog().getExistingDirectory(this,"Workplace directory");
    ui->workplace_linedit->setText(path);
}

void SettingsDialog::saveSettings()
{
    QSettings settings("lo21-maxetdam", "NotesManager");
    settings.setValue("workplace", ui->workplace_linedit->text());
    if(NotesManager::getInstance()->getPath() != ui->workplace_linedit->text()){
        NotesManager::getInstance()->load(workplace());
    }
    settings.setValue("binary_copy", ui->copy_binary->isChecked());
}
