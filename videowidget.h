#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "notewidget.h"
#include <QPushButton>
#include <QPlainTextEdit>
#include <phonon>
#include <QFileDialog>
#include "notesmanager.h"
#include "binary.h"
#include "binarywidget.h"

/*! \class VideoWidget
 * \brief Widget permettant la visualisation et l'édition d'une note de type Video dans l'interface graphique
 */
class VideoWidget : public BinaryWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(Video* video, QWidget* parent = 0);
signals:

public slots:
    void updateBinaryWidget();
    void player();
    void changePath();
    void restartPlayer();
private :
    Phonon::VideoPlayer *videoPlayer;
    QPushButton *play, *restart;
    bool playing;
    QPlainTextEdit* description;
};

#endif // VIDEOWIDGET_H
