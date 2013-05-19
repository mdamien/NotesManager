#include "binary.h"

Binary::Binary(const unsigned int id, const QString& title, const QString& desc, const QString& path) : Note(id, title), description(desc), path(path)
{

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

Video::Video(const unsigned int id, const QString& title, const QString& desc, const QString& path) : Binary(id, title, desc, path)
{

}

Audio::Audio(const unsigned int id, const QString& title, const QString& desc, const QString& path) : Binary(id, title, desc, path)
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
