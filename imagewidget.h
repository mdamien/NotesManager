#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QImage>

class ImageWidget : public QWidget
{
public:
    ImageWidget(const QString& filename = "", QWidget* parent = 0);

protected :
    QImage* image;
};

#endif // IMAGEWIDGET_H
