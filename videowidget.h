#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "notewidget.h"
#include <QPushButton>
#include <Phonon>
#include <QFileDialog>

class VideoWidget : public NoteWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(const QString& filePath = "", const QString& tit = "", const QString& desc = "", QWidget* parent = 0);
    
signals:
    
public slots:
    void player();
    void openExplorer();
    void restartPlayer();
private :
    Phonon::VideoPlayer *videoPlayer;
    QPushButton *path, *play, *restart;
    bool playing;
    QLineEdit* fileName;
    QString filePath;
};

#endif // VIDEOWIDGET_H
