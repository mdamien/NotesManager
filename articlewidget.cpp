#include "articlewidget.h"

using namespace std;

ArticleWidget::ArticleWidget(const QString& tit, const QString& cont, QWidget* parent) : NoteWidget(tit, cont, parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(title);
    layout->addWidget(content);

    setLayout(layout);
    std::map<QString, NotesFactory*>* facto = NotesManager::getInstance()->getFactory();
    note = new Article(NotesFactory::getNewId(), tit, cont);

    NotesManager::getInstance()->addRessource(note);
}
