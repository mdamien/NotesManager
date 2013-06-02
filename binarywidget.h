#ifndef BINARYWIDGET_H
#define BINARYWIDGET_H

#include "notewidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "binary.h"

/*! \class BinaryWidget
 * \brief Widget abstrait permettant la visualisation et l'édition d'une note de type Binary dans l'interface graphique
 */
class BinaryWidget : public NoteWidget
{
    Q_OBJECT
public:
    BinaryWidget(Binary* bin,QWidget* parent = 0);
    Note* getNote();

public slots:
    void updateNote();
    virtual void changePath() = 0;
    virtual void updateBinaryWidget() = 0;
protected:
    QHBoxLayout* binaryLayout;
    QPushButton* changePathB;
    QLineEdit* path;
    QTextEdit* description;
    Binary* note;
};

#endif // BINARYWIDGET_H
