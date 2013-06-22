#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>
#include <QDebug>
#include "savetextexport.h"
#include <QFileDialog>
#include "aboutdialog.h"
#include <QDesktopServices>
#include <QUrl>

MainWindow* MainWindow::mw = 0;

/*!
 *  Retourne l'instance courante de la MainWindow
 *
 *  \param parent : parent de la MainWindow
 *  \return MainWindow* : instance unique de la MainWindow
 */
MainWindow* MainWindow::getInstance(QWidget *parent)
{
    if(mw){
        return mw;
    }
    else {
        mw = new MainWindow(parent);
        return mw;
    }
}

/*!
 * \brief Supprime l'instance courante de la MainWindow
 */
void MainWindow::deleteInstance()
{
    if(mw){
        delete mw;
        mw = 0;
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nm = NotesManager::getInstance();
    tm = TagManager::getInstance();
    currentNote = NULL;

    updateTagsList();

    trash = Trash::getInstance();
    checkedTags = new QSet<QListWidgetItem*>();
    filteredNotes = new QSet<Note*>();
    ui->tabWidget->setCurrentIndex(0);
    updateNotesList();

    connect(ui->tabs,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    connect(ui->menuAdd, SIGNAL(triggered(QAction*)), this, SLOT(addNote(QAction*)));
    connect(ui->actionNew, SIGNAL(triggered()),this,SLOT(newNote()));
    connect(ui->actionOpen, SIGNAL(triggered()),this,SLOT(chooseNoteToOpen()));
    connect(ui->actionSave, SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionClose, SIGNAL(triggered()),this,SLOT(closeNote()));
    connect(ui->notes_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(loadSidebarNote(QListWidgetItem*)));
    connect(ui->tag_list, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(updateTag(QListWidgetItem*)));
    connect(ui->tag_set, SIGNAL(clicked()),this,SLOT(addTag()));
    connect(ui->tag_remove, SIGNAL(clicked()),this,SLOT(removeTag()));
    connect(ui->tag_lineedit, SIGNAL(textChanged(QString)),this,SLOT(tagSearch()));
    connect(ui->tag_search, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(loadSidebarNote(QListWidgetItem*)));
    connect(ui->tag_filter, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(addFilter(QListWidgetItem*)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(filterNotesList(int)));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(openSettings()));
    connect(ui->menuView, SIGNAL(triggered(QAction*)), this, SLOT(displayView(QAction*)));
    connect(ui->actionTrash, SIGNAL(triggered()), trash, SLOT(showTrash()));
    connect(ui->actionExportAsHTML, SIGNAL(triggered()), this, SLOT(saveHTML()));
    connect(ui->actionExportAsLatex, SIGNAL(triggered()), this, SLOT(saveLatex()));
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(ui->html_showsource, SIGNAL(clicked()),this,SLOT(toogleShowHTMLSource()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete filteredNotes;
    delete checkedTags;
}

/*!
 * \brief SLOT gérant le clic sur une action du menu du choix d'affichage : permet de n'utiliser qu'une méthode pour 4 actions
 * \param a : QAction sur laquelle l'utilisateur a cliqué
 */
void MainWindow::displayView(QAction* a)
{
    if(a == ui->actionEditor)
    {
        ui->tabs->setCurrentIndex(0);
    }
    else if(a == ui->actionText)
    {
        ui->tabs->setCurrentIndex(1);
    }
    else if(a == ui->actionHTML)
    {
        ui->tabs->setCurrentIndex(2);
    }
    else if(a == ui->actionLaTeX)
    {
        ui->tabs->setCurrentIndex(3);
    }
}

/*!
 * \brief Met à jour la liste des Notes que l'utilisateur peut charger en fonction de l'onglet de filtre sur lequel il est
 */
void MainWindow::updateNotesList()
{
    ui->notes_list->clear();

    if(ui->tabWidget->currentIndex() != 2)
    {
        for(NotesManager::Iterator it = nm->begin();it != nm->end();++it)
        {
            if((*it)->isLoaded())
            {
                QListWidgetItem* item = new NoteListItem((*it)->getTitle(),(*it));
                ui->notes_list->addItem(item);
            }
        }
    }
    else
    {
        for(QSet<Note*>::Iterator it = filteredNotes->begin(); it != filteredNotes->end(); ++it)
        {
            QListWidgetItem* item = new NoteListItem((*it)->getTitle(),(*it));
            ui->notes_list->addItem(item);
        }
    }
}

/*!
 * \brief Met à jour la liste des tags affichés en fonction de la note affichée à l'utilisateur
 */
void MainWindow::updateTagsList(){
    ui->tag_list->clear();

    if(currentNote != NULL){
        for(TagManager::Iterator it = tm->begin();it != tm->end();++it){
            QListWidgetItem* item = new TagListItem((*it)->getName(),(*it));
            if((*it)->contains(currentNote->getNote())){
                item->setCheckState(Qt::Checked);
            }
            else{
                item->setCheckState(Qt::Unchecked);
            }
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            ui->tag_list->addItem(item);
        }
    }
    tagSearch();

    //Initialisation de la liste des tags pour le filtrage au démarrage
    {
    if(ui->tag_filter->count() == 0)
        for(TagManager::Iterator it = tm->begin();it != tm->end();++it)
        {
            QListWidgetItem* item = new TagListItem((*it)->getName(),(*it));
            item->setCheckState(Qt::Unchecked);
            ui->tag_filter->addItem(item);
        }
    }
}

/*!
 * \brief Met à jour le tag sélectionné
 * \param item : Widget contenant un tag en attribut, ce tag sera mis à jour
 */
void MainWindow::updateTag(QListWidgetItem *item)
{
    TagListItem* i = (TagListItem*)item;
    bool checked = i->checkState() == Qt::Checked;
    Tag* tag = i->getTag();
    if(currentNote != NULL)
    {
        if(checked && !tag->contains(currentNote->getNote())){
            tag->addNote(currentNote->getNote());
        }
        if(!checked && tag->contains(currentNote->getNote())){
            tag->removeNote(currentNote->getNote());
        }
        nm->setNoteModified();
    }
}

/*!
 * Met à jour la liste des notes ayant pour tag celui entré
 */
void MainWindow::tagSearch()
{
    QString name = ui->tag_lineedit->text();
    ui->tag_search->clear();
    for(TagManager::Iterator it = tm->begin();it != tm->end();++it){
        if((*it)->getName().contains(name)){
            for(Tag::Iterator it2 = (*it)->begin();it2 != (*it)->end();++it2){
                QListWidgetItem* item = new NoteListItem((*it)->getName() +" - "+ (*it2)->getTitle(),(*it2));
                ui->tag_search->addItem(item);
            }
        }
    }
}

/*!
 * \brief Ajoute un nouveau tag à la liste des tags en cliquant sur le bouton d'ajout de tag dans l'interface
 */
void MainWindow::addTag()
{
    if(currentNote != NULL)
    {
        QString txt = ui->tag_lineedit->text();
        if(txt.length() > 0)
        {
            Tag* t = tm->getTag(txt);
            if (t == NULL)
            {
                t = new Tag(txt);
                t->addNote(currentNote->getNote());
                tm->addTag(t);
                QListWidgetItem* item = new TagListItem(t->getName(),t);
                item->setCheckState(Qt::Unchecked);
                ui->tag_filter->addItem(item);
            }
            else
            {
                t->addNote(currentNote->getNote());
            }
        }
        nm->setNoteModified();
        updateTagsList();
    }
}
void MainWindow::removeTag()
{
    QString txt = ui->tag_lineedit->text();
    if(txt.length() > 0)
    {
        tm->removeTag(txt);
    }
    nm->setNoteModified();
    updateTagsList();
}

/*!
 * \brief Efface le contenu dans l'éditeur permettant d'accueillir une nouvelle note.
 */
void MainWindow::newNote()
{
    clearLayout(ui->editor_area->layout());
    currentNote = NULL;
    updateTagsList();
    removeTextFromTabs();
}

/*!
 * \brief Supprime le texte des onglets HTML, Text et LaTeX
 */
void MainWindow::removeTextFromTabs()
{
    ui->text_textedit->setPlainText("");
    ui->html_textedit->setHtml("");
    ui->latex_textedit->setPlainText("");
}

/*!
 * \brief Ferme la note courante, ouverte dans l'éditeur et les onglets
 */
void MainWindow::closeCurrentNote()
{
    if(currentNote != NULL)
    {
        currentNote->getNote()->setLoaded(false);
        clearLayout(ui->editor_area->layout());
        currentNote = NULL;
        updateNotesList();
        updateTagsList();
        removeTextFromTabs();
    }
}

/*!
 * \brief SLOT appellant la fonction de fermeture de note
 */
void MainWindow::closeNote()
{
    closeCurrentNote();
    nm->setNoteModified();
}

/*!
 * \brief SLOT permettant à l'utilisateur de choisir facilement une note à ouvrir et charger
 */
void MainWindow::chooseNoteToOpen()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose note",nm->getPath(),"*.note");
    qDebug() << "path:" << path;
    QFileInfo info(path);
    Note* n = nm->loadNote(info.baseName().toUInt());
    loadNote(makeWidget(n));
    nm->setNoteModified();
}

/*!
 * \brief SLOT déclenchant l'ouverture d'une fenêtre contenant les paramètres du logiciel
 */
void MainWindow::openSettings()
{
    QString old_path = nm->getPath();
    SettingsDialog d;
    if(d.exec() == QDialog::Accepted){
        if(d.workplace() != old_path){
            updateNotesList();
            updateTagsList();
            newNote();
        }
    }
}

/*!
 * \brief Appelle le SaveTextExport pour sauvegarder toutes les modifications non enregistrées
 */
void MainWindow::save()
{
    SaveTextExport().save();
}

/*!
 * \brief Charge la note passée en paramètre sous forme de widget
 * \param n : Widget à charger, il contient une note
 */
void MainWindow::loadNote(NoteWidget *n)
{
    if(n == NULL){
        updateNotesList();
        updateTagsList();
        return;
    }
    clearLayout(ui->editor_area->layout());
    ui->editor_area->layout()->addWidget(n);
    currentNote = n;
    n->getNote()->setLoaded(true);
    updateNotesList();
    updateTagsList();
}

/*!
 * \brief Crée un widget en fonction de la note passée en paramètre
 * \param note : Note à partir de laquelle on veut créer un widget
 * \param parent : Parent du widget retourné
 * \return Retourne le widget créé depuis la note donnée
 */
NoteWidget *MainWindow::makeWidget(Note *note, QWidget* parent)
{
    if(note == NULL){
        return NULL;
    }
    NoteWidget* n = NULL;
    QString name = typeid(*note).name();
    if(name == typeid(Article).name())
        n = new ArticleWidget((Article*)note, parent);
    else if(name == typeid(Document).name())
        n = new DocumentWidget((Document*)note, parent);
    else if(name == typeid(Image).name())
        n = new ImageWidget((Image*)note, parent);
    else if(name == typeid(Audio).name())
        n = new AudioWidget((Audio*)note, parent);
    else if(name == typeid(Video).name())
        n = new VideoWidget((Video*)note, parent);
    else
        qDebug() << "ERROR:Note type "+name+" not implemented yet in Qt Widgets";
    connect(n,SIGNAL(titleChanged(QString)),this,SLOT(updateNotesList()));
    return n;
}

/*!
 * \brief SLOT gérant le changement d'onglet du tableau d'affichage des notes
 * \param i : Indice du nouvel onglet
 */
void MainWindow::tabChanged(int i)
{
    if(currentNote != NULL){
        switch(i)
        {
        case 1:    //ExportText
            ui->text_textedit->setPlainText(currentNote->getNote()->exportNote(nm->getExporter("Text")));
            break;
        case 2 :   //ExportHTML
            if(ui->html_showsource->isChecked()){
                ui->html_textedit->setPlainText(currentNote->getNote()->exportNote(nm->getExporter("HTML")));
                break;
            }
            ui->html_textedit->setHtml(currentNote->getNote()->exportNote(nm->getExporter("HTML")));
            break;
        case 3 :   //ExportLaTeX
            ui->latex_textedit->setPlainText(currentNote->getNote()->exportNote(nm->getExporter("LaTeX")));
            break;
        }
    }
}

/*!
 * \brief Supprime tous les widgets contenus dans le layout passé en paramètre et désalloue la mémoire occupée sur demande
 * \param layout : Layout à "nettoyer"
 * \param deleteWidgets : Indique s'il faut désallouer la mémoire des widgets (true par défaut)
 */
void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        else if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

/*!
 * \brief SLOT ajoutant une note à la note courante en fonction de l'action choisie par l'utilisateur. S'il n'y a pas de note courante, la note créée est chargée et devient la note courante.
 * \param a : Action choisie par l'utilisateur
 */
void MainWindow::addNote(QAction* a)
{
    NotesManager* nm = NotesManager::getInstance();

    Note* n = NULL;

    if(a == ui->actionArticle)
    {
        n = new Article(nm->getNewId(),"Titre Article","Contenu");
    }
    else if(a == ui->actionImage)
    {
        n = new Image(nm->getNewId(),"Titre Image","Description");
    }
    else if(a == ui->actionDocument)
    {
        n = new Document(nm->getNewId(),"Titre Document");
    }
    else if(a == ui->actionAudio)
    {
        n = new Audio(nm->getNewId(),"Titre Audio","Description");
    }
    else if(a == ui->actionVideo)
    {
        n = new Video(nm->getNewId(),"Titre Video","Description");
    }
    if(n == NULL)
    {
        return;
    }
    nm->addRessource(n);
    nm->setNoteModified();

    NoteWidget* w = makeWidget(n,this);

    if(currentNote == NULL){
        n->setLoaded(true);
        loadNote(w);
        updateNotesList();
    }
    else{
        if(QString(currentNote->metaObject()->className()) == "DocumentWidget"){
            ((DocumentWidget*)currentNote)->addNoteWidget(w);
            ((Document*)((DocumentWidget*)currentNote)->getNote())->addSubNote(n);
        }else{
            Document* d = new Document(nm->getNewId(),"Document");
            nm->addRessource(d);
            d->addSubNote(currentNote->getNote());
            currentNote->getNote()->setLoaded(false);
            d->setLoaded(true);
            d->addSubNote(n);
            loadNote(makeWidget(d,this));
            updateNotesList();
        }
    }
}

/*!
 * \brief Charge la note sur laquelle l'utilisateur a cliqué depuis la liste des notes.
 * \param item : Contient une note qui sera ensuite utilisé. Facilite la liaison interface-objet.
 */
void MainWindow::loadSidebarNote(QListWidgetItem *item)
{
    NoteListItem* i = (NoteListItem*) item;
    loadNote(makeWidget(i->getNote(),this));
    ui->tabs->setCurrentIndex(0);
}

/*!
 * \brief SLOT permettant de supprimer graphiquement un widget (une note) et de l'ajouter à la Trash
 * \param nw : Widget qui sera supprimé
 */
void MainWindow::deleteWidget(NoteWidget* nw)
{
    if(currentNote == nw) //Permet de supprimer TOUTE la note (article etc seul : OK, document entier : OK)
    {
        Trash::getInstance()->addItem(nw->getNote());
        closeNote();
    }
    else //On veut supprimer une partie du document
    {
        Document* doc = ((Document*)currentNote->getNote());
        Trash::getInstance()->addItem(nw->getNote(), doc);
        doc->removeSubNote(nw->getNote());
        closeNote();

        if(doc->getNumberOfSubNotes()) //S'il reste des Notes dans le document on le recharge avec celles-ci
            loadNote(makeWidget(doc, this));
    }
    NotesManager::getInstance()->setNoteModified();
}

/*!
 * \brief Propose à l'utilisateur de sauvegarder si des modifications ont été aperçues
 * \param e
 */
void MainWindow::closeEvent(QCloseEvent* e)
{
    if(nm->noteModified()){
        int answer = QMessageBox::question(this, "Closing NotesManager", "You have unsaved changes (tags, notes modifications...).\nWould you like to save these changes ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if(answer == QMessageBox::Yes)
        {
            emit save();
        }
        if(answer == QMessageBox::Yes || answer == QMessageBox::No)
            e->accept();
        else
            e->ignore();
    }
}

/*!
 * \brief Enregistre la note courante au format HTML
 */
void MainWindow::saveHTML()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save as HTML");
    if(filename != ""){
        if(!filename.endsWith(".html")){
            filename.append(".html");
        }
        QFile f( filename );
        f.open( QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&f);
        out << currentNote->getNote()->exportNote(nm->getExporter("HTML"));
        f.close();
    }
}

/*!
 * \brief Enregistre la note courante au format LaTeX
 */
void MainWindow::saveLatex()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save as LaTeX");
    if(filename != ""){
        if(!filename.endsWith(".tex")){
            filename.append(".tex");
        }
        QFile f( filename );
        f.open( QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&f);
        out << currentNote->getNote()->exportNote(nm->getExporter("LaTeX"));
        f.close();
    }
}

/*!
 * \brief Met à jour la liste des notes filtrée en fonction des tags sélectionnés
 */
void MainWindow::updateTagFilter()
{
    ui->notes_list->clear();
    filteredNotes->clear();

    //On remplit un set contenant chaque note ayant au moins un tag
    for(QSet<QListWidgetItem*>::Iterator it = checkedTags->begin(); it != checkedTags->end(); ++it)
    {
        Tag* tag = ((TagListItem*)(*it))->getTag();
        for(Tag::Iterator itTag = tag->begin(); itTag != tag->end(); ++itTag)
        {
            filteredNotes->insert(*itTag);
        }
    }

    for(QSet<Note*>::Iterator it = filteredNotes->begin(); it != filteredNotes->end(); it++)
    {
        NoteListItem* item = new NoteListItem((*it)->getTitle(), (*it));
        ui->notes_list->addItem(item);
    }
}

/*!
 * \brief Détermine en fonction de l'onglet des tags sur lequel on est, quelles notes afficher dans la liste des notes ouvertes
 * \param tab : Indice de l'onglet des tags sélectionné
 */
void MainWindow::filterNotesList(int tab)
{
    if(tab < 2) //Si on clique sur "tag" ou "search", on affiche la liste des notes normale
    {
        updateNotesList();
        return;
    }

    //Sinon on fait une recherche personnalisée
    updateTagFilter();
}

/*!
 * \brief Ajoute un tag à la liste des tags pour filtrer les notes
 * \param item : Contient un tag qui sera ensuite utilisé. Facilite la liaison interface-objet.
 */
void MainWindow::addFilter(QListWidgetItem* item)
{
    if(item->checkState() == Qt::Checked)
    {
        checkedTags->insert(item);
    }
    else if(checkedTags->contains(item))
    {
        checkedTags->remove(item);
    }
    updateTagFilter();
}

/*!
 * \brief Recharge la note actuelle avec la précédente modification de l'utilisateur
 */
void MainWindow::undo()
{
    if(currentNote != NULL){
        nm->getHistory()->undo();
        loadNote(makeWidget(currentNote->getNote(),this));
    }
}

/*!
 * \brief Recharge la note actuelle avec la modification "suivante" de l'utilisateur (nécessite au moins un undo pour faire un redo)
 */
void MainWindow::redo()
{
    if(currentNote != NULL){
        nm->getHistory()->redo();
        loadNote(makeWidget(currentNote->getNote(),this));
    }
}

/*!
 * \brief SLOT permettant d'afficher le code source de l'onglet vue HTML
 */
void MainWindow::toogleShowHTMLSource()
{
    tabChanged(ui->tabs->currentIndex());
}

void MainWindow::showAbout()
{
    AboutDialog(this).exec();
}

void MainWindow::showHelp()
{
    QDesktopServices::openUrl(QUrl("http://dam.io/notesmanager"));
}
