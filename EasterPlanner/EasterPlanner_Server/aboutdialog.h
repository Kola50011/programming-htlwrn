/*
 * authors: Lampalzer Konstantin, Königsreiter Simon, Glavanits Marcel, Lampalzer Alexander
 * date: 21.03.2019
 * class: 5BHIF
 */

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
