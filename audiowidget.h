#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include "notewidget.h"
#include <QPushButton>
#include <phonon>
#include <QFileDialog>

class AudioWidget : public NoteWidget
{
    Q_OBJECT

public :
    explicit AudioWidget(const QString& filePath = "", const QString& tit = "", const QString& desc = "", QWidget* parent = 0);

protected :
    QPushButton *path, *play, *restart;
    bool playing;
    QLineEdit* fileName;
    Phonon::MediaObject* music;
    QString filePath;

public slots :
    void player();
    void openExplorer();
    void restartPlayer();
};

#endif // AUDIOWIDGET_H
