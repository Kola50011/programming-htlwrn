#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->notePaint, SIGNAL(clicked()),
                     this, SLOT(on_notePaint_clicked()));
}

void MainWindow::load() {
    loadNotes();
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
    ui->notePaint->clearImage();
    ui->notePaint->drawPoints(note.points);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    Note toAdd("Title", "Text", {});
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
    Note &toDisplay = notes[ui->noteList->currentRow()];
    toDisplay.title = text;
    displayNote(toDisplay);
}

void MainWindow::on_noteText_textChanged()
{
    int idx = ui->noteList->currentRow();
    if (idx != -1) {
        Note &toDisplay = notes[idx];
        toDisplay.text = ui->noteText->toPlainText();
    }
}

void MainWindow::loadNotes()
{
    std::cout << "Loading" << std::endl;
    QFile saveFile(QDir::homePath() + "/notes");
    if (saveFile.open(QFile::ReadOnly)) {
        QDataStream stream(&saveFile);
        int size;
        stream >> size;

        for (int i = 0; i < size; i++) {
            Note note;
            stream >> note;
            addNote(note);
        }

        saveFile.close();
    } else {
        std::cerr << "Could not open saveFile" << std::endl;
    }
}

void MainWindow::saveNotes() {
    std::cout << "Saving" << std::endl;
    QFile saveFile(QDir::homePath() + "/notes");
    if (saveFile.open(QFile::WriteOnly|QFile::Truncate)) {
        QDataStream out(&saveFile);
        int size{notes.size()};
        out << size;
        foreach (Note note, notes) {
            out << note;
        }
        saveFile.close();
    } else {
        std::cerr << "Could not open saveFile" << std::endl;
    }
}

void MainWindow::on_actionSave_triggered()
{
    saveNotes();
}

void MainWindow::on_actionDelete_triggered()
{
    int idx = ui->noteList->currentRow();
    delete ui->noteList->takeItem(idx);
    notes.erase(notes.begin() + idx);
    ui->notePaint->clearImage();
}

void MainWindow::on_notePaint_clicked()
{
    int idx = ui->noteList->currentRow();
    if (idx != -1) {
        Note &toChange = notes[idx];
        toChange.points = ui->notePaint->points;
    }
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(ui->notePaint->penColor, this);
    if (color.isValid()) {
        ui->notePaint->penColor = color;
    }
}

void MainWindow::on_actionErase_triggered()
{
    ui->notePaint->penColor = Qt::white;
}
