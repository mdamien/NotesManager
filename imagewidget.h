#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "notewidget.h"
#include "binary.h"

class ImageWidget : public NoteWidget
{
    Q_OBJECT
public:
    ImageWidget(Image* img,QWidget* parent = 0);
    Note* getNote();
signals:

public slots:
    void updateNote();
    void chooseImage();
private:
    QTextEdit* description;
    QLabel* image;
    QPushButton* button;
    Image* note;
};
#endif // IMAGEWIDGET_H
