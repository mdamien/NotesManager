#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <phonon>
#include "notewidget.h"
#include "binary.h"

/*! \class AudioWidget
 * \brief Widget permettant la visualisation et l'édition d'une note de type Audio dans l'interface graphique
 */
class AudioWidget : public NoteWidget
{
    Q_OBJECT
public:
    AudioWidget(Audio* img,QWidget* parent = 0);
    Note* getNote();
signals:

public slots:
    void updateNote();
    void player();
    void openExplorer();
    void restartPlayer();

protected :
    QPushButton *path, *play, *restart;
    bool playing;
    QLineEdit* fileName;
    Phonon::MediaObject* music;
    QTextEdit* description;
    Audio* note;
};

#endif // AUDIOWIDGET_H
