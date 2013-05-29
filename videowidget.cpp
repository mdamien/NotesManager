#include "videowidget.h"

VideoWidget::VideoWidget(Video* video, QWidget* parent) : note(video)
{
    description = new QPlainTextEdit(note->getDescription());
    playing = false;
    path = new QPushButton("Set Video", this);
    play = new QPushButton("Play", this);
    restart = new QPushButton("Restart", this);

    QHBoxLayout* playerLayout = new QHBoxLayout;

    fileName = new QLineEdit(filePath);
    fileName->setReadOnly(true);

    playerLayout->addWidget(path);
    playerLayout->addWidget(fileName);
    playerLayout->addWidget(play);
    playerLayout->addWidget(restart);

    videoPlayer  = new Phonon::VideoPlayer(Phonon::VideoCategory, this);

    layout->addWidget(videoPlayer);
    layout->addLayout(playerLayout);
    layout->addWidget(description);

    title->setText(note->getTitle());

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
    QString s(QFileDialog::getOpenFileName(this, "Sélectionnez un enregistrement vidéo","*.avi"));
    fileName->setText(s);
    videoPlayer->mediaObject()->clear();
    videoPlayer->mediaObject()->setCurrentSource(Phonon::MediaSource(s));
    note->setPath(s);
    if(playing)
    {
        playing = false;
    }
    note->setModified(true);
}

void VideoWidget::restartPlayer()
{
    videoPlayer->stop();
    play->setText("Play");
    playing = false;
}


void VideoWidget::updateNote()
{
    note->setTitle(title->text());
    note->setDescription(description->toPlainText());
    note->setModified(true);
}

Note* VideoWidget::getNote(){
    return note;
}
