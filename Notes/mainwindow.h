#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include "note.h"
#include "QDir"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_noteList_itemSelectionChanged();

    void on_noteTitle_textEdited(const QString &text);

    void on_noteText_textChanged();

private:
    Ui::MainWindow *ui;
    std::vector<Note> notes;

    void addNote(Note &note);
    void displayNote(Note &note);
    void loadFiles();
};

#endif // MAINWINDOW_H
