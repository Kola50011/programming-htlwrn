#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include "note.h"
#include "QDir"
#include <QPainter>
#include <QPaintEvent>
#include <QRectF>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void load();

private slots:

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_noteList_itemSelectionChanged();

    void on_noteTitle_textEdited(const QString &text);

    void on_noteText_textChanged();

    void on_actionSave_triggered();

    void on_actionDelete_triggered();

    void on_notePaint_clicked();

    void on_actionColor_triggered();

    void on_actionErase_triggered();

protected:
    void paintEvent(QPaintEvent * event)
    {
        QMainWindow::paintEvent(event);
        QPainter p(this);

        QRectF rectangle(10.0, 20.0, 80.0, 60.0);
        p.drawRect(rectangle);
    }

private:
    Ui::MainWindow *ui;
    std::vector<Note> notes;

    void addNote(Note &note);
    void displayNote(Note &note);
    void loadNotes();
    void saveNotes();
    QColorDialog colorDialog;
};

#endif // MAINWINDOW_H
