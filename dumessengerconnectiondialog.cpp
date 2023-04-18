#include "dumessengerconnectiondialog.h"
#include "ui_dumessengerconnectiondialog.h"

DuMessengerConnectionDialog::DuMessengerConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuMessengerConnectionDialog)
{
    ui->setupUi(this);
}

DuMessengerConnectionDialog::~DuMessengerConnectionDialog()
{
    delete ui;
}


