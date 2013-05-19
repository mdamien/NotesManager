#ifndef BINARY_H
#define BINARY_H

#include "note.h"

class Note;
class Binary : public Note
{
public:
    Binary(const unsigned int id, const QString& title, const QString& desc, const QString& path);
    QString getDescription() const;
    void setDescription(const QString& desc);
    QString getPath() const;
    void setPath(const QString& p);

protected :
    QString description;
    QString path;
    Binary(const Binary&);
    Binary& operator=(const Binary&);
};

//Image, Vidéo, Audio :

class Image : public Binary
{
public :
    Image(const unsigned int id, const QString& title, const QString& desc, const QString& path);

private :
    Image(const Image&);
    Image& operator=(const Image&);
    void load();
};

class Video : public Binary
{
public :
    Video(const unsigned int id, const QString& title, const QString& desc, const QString& path);

private :
    Video(const Video&);
    Video& operator=(const Video&);
    void load();
};

class Audio : public Binary
{
public :
    Audio(const unsigned int id, const QString& title, const QString& desc, const QString& path);

private :
    Audio(const Audio&);
    Audio& operator=(const Audio&);
    void load();
};

#endif // BINARY_H
