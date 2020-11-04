/*
 * Author: Lampalzer Konstantin
 * Class: 5BHIF
 * Date: 16.02.2019
 */

#ifndef ADDROUTEDIALOG_H
#define ADDROUTEDIALOG_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui
{
class AddRouteDialog;
}

class AddRouteDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit AddRouteDialog(QWidget *parent = 0);
    ~AddRouteDialog();

  private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

  private:
    Ui::AddRouteDialog *ui;

    void initGUI();
};

#endif // ADDROUTEDIALOG_H
