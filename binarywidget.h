#ifndef BINARYWIDGET_H
#define BINARYWIDGET_H

#include "notewidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "binary.h"
#include <QDir>
#include <QNetworkAccessManager>

/*! \class BinaryWidget
 * \brief Widget abstrait permettant la visualisation et l'édition d'une note de type Binary dans l'interface graphique
 */
class BinaryWidget : public NoteWidget
{
    Q_OBJECT
public:
    BinaryWidget(Binary* bin,QWidget* parent = 0);
    Note* getNote();

protected slots:
    void updateNote();
    virtual void changePath() = 0;
    virtual void updateBinaryWidget() = 0;
    void onNetworkReply(QNetworkReply* reply);
protected:
    void download(QString url);

protected:
    QHBoxLayout* binaryLayout;
    QPushButton* changePathB;
    QLineEdit* path;
    QTextEdit* description;
    Binary* note;
    QNetworkAccessManager networkManager;
    QString tmp_dest;
};

#endif // BINARYWIDGET_H
