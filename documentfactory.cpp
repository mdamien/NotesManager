#include "documentfactory.h"

DocumentFactory::DocumentFactory()
{

}

Note* DocumentFactory::buildNote(const unsigned int id, const QString& title) const
{
    return new Document(id, title);
}

Note* DocumentFactory::buildNewNote(const QString& title) const
{
    return new Document(getNewId(), title);
}

Note* DocumentFactory::buildNoteCopy(Note* note) const
{
    if(note = dynamic_cast<Document*> (note))    //Ne pas copier quelque chose qui n'est pas un Document
      return new Document((Document*) note);

    return 0;
}
