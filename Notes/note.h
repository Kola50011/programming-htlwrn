#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QFile>

class Note
{
public:
    Note(QString _title, QString _text) : title{_title}, text{_text} {};
    QString title;
    QString text;
    QString filePath;
};

#endif // NOTE_H
