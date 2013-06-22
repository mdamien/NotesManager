#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QNetworkProxy>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->workplace_linedit->setText(workplace());
    ui->copy_binary->setChecked(binaryCopy());
    ui->proxy->setText(proxy());
    ui->proxy_port->setValue(proxy_port().toInt());

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
    return settings.value("workplace","../workplace").toString();
}
QString SettingsDialog::proxy()
{
    QSettings settings("lo21-maxetdam", "NotesManager");
    return settings.value("proxy","").toString();
}
QString SettingsDialog::proxy_port()
{
    QSettings settings("lo21-maxetdam", "NotesManager");
    return settings.value("proxy_port","").toString();
}

void SettingsDialog::setProxyApplicationWide()
{
    if(proxy() == ""){
        QNetworkProxy p;
        p.setType(QNetworkProxy::NoProxy);
        QNetworkProxy::setApplicationProxy(p);
    }else{
        QNetworkProxy p;
        p.setType(QNetworkProxy::HttpProxy);
        p.setHostName(proxy());
        p.setPort(proxy_port().toInt());
        QNetworkProxy::setApplicationProxy(p);
    }
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
    settings.setValue("proxy", ui->proxy->text());
    settings.setValue("proxy_port", QString::number(ui->proxy_port->value()));
    setProxyApplicationWide();
    settings.setValue("binary_copy", ui->copy_binary->isChecked());
}
