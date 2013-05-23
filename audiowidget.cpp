#include "audiowidget.h"

AudioWidget::AudioWidget(const QString& filePath, const QString& tit, const QString& desc, QWidget* parent) : NoteWidget(tit, desc, parent), filePath(filePath)
{
    playing = false;
    path = new QPushButton("Set Audio", this);
    play = new QPushButton("Play", this);
    restart = new QPushButton("Restart", this);
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* playerLayout = new QHBoxLayout;

    fileName = new QLineEdit;
    fileName->setReadOnly(true);

    layout->addWidget(title);
    playerLayout->addWidget(path);
    playerLayout->addWidget(fileName);
    playerLayout->addWidget(play);
    playerLayout->addWidget(restart);
    layout->addLayout(playerLayout);
    layout->addWidget(content);
    setLayout(layout);
    music = Phonon::createPlayer(Phonon::MusicCategory);
    QObject::connect(path, SIGNAL(clicked()), this, SLOT(openExplorer()));
    QObject::connect(play, SIGNAL(clicked()), this, SLOT(player()));
    QObject::connect(restart, SIGNAL(clicked()), this, SLOT(restartPlayer()));
}

void AudioWidget::player()
{
    if(playing)
    {
        music->pause();
        play->setText("Continue");
    }
    else
    {
        music->play();
        play->setText("Pause");
    }
    playing = !playing;
}

void AudioWidget::openExplorer()
{
    QString a(QFileDialog::getOpenFileName(this, "Sélectionnez un enregistrement audio", "*.mp3;*.wav"));
    fileName->setText(a);
    music->setCurrentSource(a);
    filePath = a;
    if(playing)
    {
        playing = false;
    }
}

void AudioWidget::restartPlayer()
{
    if(playing)
    {
        music->stop();
        play->setText("Play");
        playing = false;
    }
}
