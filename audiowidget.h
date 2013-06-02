#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <phonon>
#include "notewidget.h"
#include "binary.h"
#include "binarywidget.h"

/*! \class AudioWidget
 * \brief Widget permettant la visualisation et l'édition d'une note de type Audio dans l'interface graphique
 */
class AudioWidget : public BinaryWidget
{
    Q_OBJECT
public:
    AudioWidget(Audio* img,QWidget* parent = 0);
signals:

public slots:
    void updateBinaryWidget();
    void player();
    void changePath();
    void restartPlayer();

protected :
    QPushButton *play, *restart;
    bool playing;
    Phonon::MediaObject* music;
};

#endif // AUDIOWIDGET_H
