#include "note.h"
QDataStream &operator <<(QDataStream &out, const Note &note) {
    out << note.title << note.text;
    return out;
}

QDataStream &operator >>(QDataStream &in, Note &note) {
    QString title;
    QString text;
    in >> title >> text;
    note = Note(title, text);
    return in;
}
