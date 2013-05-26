#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "notewidget.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QFileDialog>
#include <QObject>
#include "notesmanager.h"

class ImageWidget : public NoteWidget
{
    Q_OBJECT

public:
    ImageWidget(const QString& filePath = "", const QString& tit = "Title", const QString& desc = "Description", QWidget* parent = 0);

signals :

protected :
    QString filePath;
    QLabel* image;
    QPushButton* path;

public slots :
    void openExplorer();
};

#endif // IMAGEWIDGET_H
