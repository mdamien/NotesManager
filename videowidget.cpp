#include "videowidget.h"

VideoWidget::VideoWidget(const QString& filePath, const QString& tit, const QString& desc, QWidget* parent) : NoteWidget(tit, desc, parent), filePath(filePath)
{   
    playing = false;
    path = new QPushButton("Set Audio", this);
    play = new QPushButton("Play", this);
    restart = new QPushButton("Restart", this);

    QHBoxLayout* playerLayout = new QHBoxLayout;
    QVBoxLayout* layout = new QVBoxLayout;

    fileName = new QLineEdit(filePath);
    fileName->setReadOnly(true);

    playerLayout->addWidget(path);
    playerLayout->addWidget(fileName);
    playerLayout->addWidget(play);
    playerLayout->addWidget(restart);


    videoPlayer  = new Phonon::VideoPlayer(Phonon::VideoCategory, this);

    layout->addWidget(title);
    layout->addWidget(videoPlayer);
    layout->addLayout(playerLayout);
    layout->addWidget(content);

    setLayout(layout);

 //   videoPlayer->play(Phonon::MediaSource("MVI_0040.avi"));
 //   videoPlayer->mediaObject()->setCurrentSource(Phonon::MediaSource(filePath));
    videoPlayer->setMinimumSize(400, 400);
    QObject::connect(path, SIGNAL(clicked()), this, SLOT(openExplorer()));
    QObject::connect(play, SIGNAL(clicked()), this, SLOT(player()));
    QObject::connect(restart, SIGNAL(clicked()), this, SLOT(restartPlayer()));
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
        videoPlayer->play();
        play->setText("Pause");
    }
    playing = !playing;
}

void VideoWidget::openExplorer()
{
    QString s(QFileDialog::getOpenFileName(this, "Sélectionnez un enregistrement vidéo"));
    fileName->setText(s);
    videoPlayer->mediaObject()->clear();
    videoPlayer->mediaObject()->setCurrentSource(Phonon::MediaSource(s));
    filePath = s;
    if(playing)
    {
        playing = false;
    }
}

void VideoWidget::restartPlayer()
{
    videoPlayer->stop();
    play->setText("Play");
    playing = false;
}
