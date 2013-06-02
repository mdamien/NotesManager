#include "videowidget.h"

VideoWidget::VideoWidget(Video* video, QWidget* parent) :BinaryWidget(video,parent)
{
    playing = false;
    play = new QPushButton("Play", this);
    restart = new QPushButton("Restart", this);

    binaryLayout->addWidget(play);
    binaryLayout->addWidget(restart);

    videoPlayer  = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    layout->insertWidget(1,videoPlayer);

    title->setText(note->getTitle());

    videoPlayer->setMinimumSize(400, 400);
    updateBinaryWidget();

    connect(play, SIGNAL(clicked()), this, SLOT(player()));
    connect(restart, SIGNAL(clicked()), this, SLOT(restartPlayer()));
}

void VideoWidget::player()
{
    if(playing)
    {
        videoPlayer->pause();
        play->setText("Continue");
    }
    else
    {
        if(videoPlayer->mediaObject()->currentSource().fileName() == "")
        {
            videoPlayer->mediaObject()->clear();
            videoPlayer->mediaObject()->setCurrentSource(Phonon::MediaSource(note->getPath()));
        }
        videoPlayer->play();
        play->setText("Pause");
    }
    playing = !playing;
}


void VideoWidget::updateBinaryWidget(){
    if(note->getPath() != ""){
        videoPlayer->mediaObject()->clear();
        videoPlayer->mediaObject()->setCurrentSource(Phonon::MediaSource(note->getPath()));
        playing = false;
        play->setText("Play");
    }
}


void VideoWidget::restartPlayer()
{
    videoPlayer->stop();
    play->setText("Play");
    playing = false;
}

void VideoWidget::changePath()
{
    path->setText(QFileDialog::getOpenFileName(this, "Sélectionnez un enregistrement vidéo","*.avi"));
}

