#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "notewidget.h"
#include "binary.h"
#include "binarywidget.h"

/*! \class ImageWidget
 * \brief Widget permettant la visualisation et l'édition d'une note de type Image dans l'interface graphique
 */
class ImageWidget : public BinaryWidget
{
    Q_OBJECT
public:
    ImageWidget(Image* img,QWidget* parent = 0);
signals:

public slots:
    void updateBinaryWidget();
    void changePath();
private:
    QLabel* image;
};
#endif // IMAGEWIDGET_H
