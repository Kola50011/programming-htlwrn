#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Note toAdd("Lorem", "Ipsum");
    addNote(toAdd);

    loadFiles();
}

void MainWindow::addNote(Note& note) {
    notes.push_back(note);
    ui->noteList->addItem(note.title);

    if ( notes.size() == 1) {
        displayNote(note);
    }
}

void MainWindow::displayNote(Note& note) {
    ui->noteTitle->setText(note.title);
    ui->noteText->setText(note.text);
    if (ui->noteList->currentItem()) {
        ui->noteList->currentItem()->setText(note.title);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    Note toAdd("Title", "Text");
    addNote(toAdd);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_noteList_itemSelectionChanged()
{
    displayNote(notes.at(ui->noteList->currentRow()));
}

void MainWindow::on_noteTitle_textEdited(const QString &text)
{
    Note toDisplay = notes.at(ui->noteList->currentRow());
    toDisplay.title = text;
    displayNote(toDisplay);
}

void MainWindow::on_noteText_textChanged()
{
    int idx = ui->noteList->currentRow();
    if (idx != -1) {
        Note toDisplay = notes.at(idx);
        toDisplay.text = ui->noteText->toPlainText();
    }
}

void MainWindow::loadFiles()
{
    QDir dir("/home/koka/Desktop/test");
    foreach(auto entry, dir.entryInfoList()) {
        if (entry.isFile()) {
            QFile file(entry.absoluteFilePath());

            if (file.open(QFile::ReadOnly | QFile::Text)) {
                QTextStream stream(&file);

                QFileInfo fileInfo(file.fileName());
                Note toAdd(fileInfo.fileName(), stream.readAll());
                toAdd.filePath = entry.absoluteFilePath();
                file.close();

                addNote(toAdd);
            }
        }
    }
}
