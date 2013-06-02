#include "binary.h"
#include "settingsdialog.h"
#include <QDir>
#include "qdebug.h"

Binary::Binary(const unsigned int id, const QString& title, const QString& desc, const QString& p) : Note(id, title), description(desc)
{
    setPath(p);
}

QString Binary::getDescription() const
{
    return description;
}
void Binary::setDescription(const QString& desc)
{
    description = desc;
}

QString Binary::getPath() const
{
    return path;
}

void Binary::setPath(const QString& p)
{
    path = p;
}

Image::Image(const unsigned int id, const QString& title, const QString& desc, const QString& path) : Binary(id, title, desc, path)
{

}

Image::Image(Image* im) : Binary(im->getId(), im->getTitle(), im->getDescription(),im->getPath())
{

}

Video::Video(const unsigned int id, const QString& title, const QString& desc, const QString& path) : Binary(id, title, desc, path)
{

}

Video::Video(Video* v) : Binary(v->getId(), v->getTitle(), v->getDescription(), v->getPath())
{

}

Audio::Audio(const unsigned int id, const QString& title, const QString& desc, const QString& path) : Binary(id, title, desc, path)
{

}

Audio::Audio(Audio* a) : Binary(a->getId(), a->getTitle(), a->getDescription(), a->getPath())
{

}

//Binary ne possède pas load, et est donc bien abstraite, ses filles ont bien load

void Image::load()
{

}

void Video::load()
{

}

void Audio::load()
{

}
