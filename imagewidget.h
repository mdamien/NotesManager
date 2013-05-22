#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QFileDialog>
#include <QObject>

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(const QString& filename = "", const QString& tit = "Title", const QString& desc = "Description", QWidget* parent = 0);

signals :

protected :
    QLineEdit* title;
    QTextEdit* description;
    QString filename;
    QLabel* image;
    QPushButton* path;

public slots :
    void openExplorer();
};

#endif // IMAGEWIDGET_H
