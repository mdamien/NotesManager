#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "notewidget.h"
#include <QPushButton>
#include <QPlainTextEdit>
#include <phonon>
#include <QFileDialog>
#include "notesmanager.h"
#include "binary.h"

/*! \class VideoWidget
 * \brief Widget permettant la visualisation et l'édition d'une note de type Video dans l'interface graphique
 */
class VideoWidget : public NoteWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(Video* video, QWidget* parent = 0);
    Note* getNote();
signals:

public slots:
    void updateNote();
    void player();
    void openExplorer();
    void restartPlayer();
private :
    Phonon::VideoPlayer *videoPlayer;
    QPushButton *path, *play, *restart;
    bool playing;
    QLineEdit* fileName;
    QString filePath;
    QPlainTextEdit* description;
    Video* note;
};

#endif // VIDEOWIDGET_H
