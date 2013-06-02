#include "audiowidget.h"
#include <QFileDialog>
#include <QDebug>
AudioWidget::AudioWidget(Audio* audio, QWidget* parent):BinaryWidget(audio,parent)
{
    playing = false;
    play = new QPushButton("Play", this);
    restart = new QPushButton("Restart", this);
    binaryLayout->addWidget(play);
    binaryLayout->addWidget(restart);

    music = Phonon::createPlayer(Phonon::MusicCategory);

    updateBinaryWidget();

    connect(play, SIGNAL(clicked()), this, SLOT(player()));
    connect(restart, SIGNAL(clicked()), this, SLOT(restartPlayer()));
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

void AudioWidget::changePath()
{
    path->setText(QFileDialog::getOpenFileName(this,"Sélectionnez un enregistrement audio", "*.mp3;*.wav"));
}

void AudioWidget::restartPlayer()
{
    music->stop();
    play->setText("Play");
    playing = false;
}
void AudioWidget::updateBinaryWidget(){
    if(note->getPath() != ""){
        music->setCurrentSource(note->getPath());
        playing = false;
        play->setText("Play");
    }
}
