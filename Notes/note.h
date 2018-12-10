#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QFile>
#include <QDataStream>

class Note
{
public:
    Note(QString _title, QString _text) : title{_title}, text{_text} {};
    Note() {};
    QString title;
    QString text;
    QString filePath;
    friend QDataStream &operator <<(QDataStream &out, const Note &note);
    friend QDataStream &operator >>(QDataStream &in, Note &note);
};

#endif // NOTE_H
