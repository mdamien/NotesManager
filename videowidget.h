#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "notewidget.h"

class VideoWidget : public NoteWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(const QString& filePath = "", const QString& tit = "", const QString& desc = "", QWidget* parent = 0);
    
signals:
    
public slots:
    
};

#endif // VIDEOWIDGET_H
