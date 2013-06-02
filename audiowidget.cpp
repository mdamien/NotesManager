#include "audiowidget.h"
#include <QFileDialog>

AudioWidget::AudioWidget(Audio* audio, QWidget* parent):NoteWidget(parent),note(audio)
{
    description = new QTextEdit(note->getDescription());
    title->setText(note->getTitle());

    playing = false;
    path = new QPushButton("Set Audio", this);
    play = new QPushButton("Play", this);
    restart = new QPushButton("Restart", this);
    QHBoxLayout* playerLayout = new QHBoxLayout;

    fileName = new QLineEdit(note->getPath());
    fileName->setReadOnly(true);

    playerLayout->addWidget(path);
    playerLayout->addWidget(fileName);
    playerLayout->addWidget(play);
    playerLayout->addWidget(restart);
    layout->addLayout(playerLayout);
    layout->addWidget(description);

    music = Phonon::createPlayer(Phonon::MusicCategory);

    if(note->getPath() != "")
        music->setCurrentSource(note->getPath());

    connect(description,SIGNAL(textChanged()),this,SLOT(updateNote()));
    connect(path, SIGNAL(clicked()), this, SLOT(openExplorer()));
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

void AudioWidget::openExplorer()
{
    QString a(QFileDialog::getOpenFileName(this, "Sélectionnez un enregistrement audio", "*.mp3;*.wav"));
    if(a != note->getPath())
    {
        fileName->setText(a);
        music->setCurrentSource(a);
        playing = false;
        play->setText("Play");
        NotesManager::getInstance()->getHistory()->addAndExec(
                    new ModifyBinaryPath(note,a));
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

void AudioWidget::restartPlayer()
{
    music->stop();
    play->setText("Play");
    playing = false;
}

/*!
 * \brief Met à jour le contenu de l'audio en fonction de ce qu'a fait l'utilisateur
 */
void AudioWidget::updateNote()
{
    NoteWidget::updateNote();
    if(note->getDescription() != description->toPlainText()){
        NotesManager::getInstance()->getHistory()->addAndExec(
                    new ModifyBinaryDescription(note,description->toPlainText()));
        note->setModified(true);
        NotesManager::getInstance()->setNoteModified();
    }
}

/*!
 * \brief Renvoie la note que contient le widget
 * \return Note contenue par le widget.
 */
Note* AudioWidget::getNote()
{
    return note;
}
