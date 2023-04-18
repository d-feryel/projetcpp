#include "quitter.h"
#include "ui_quitter.h"

quitter::quitter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quitter)
{
    ui->setupUi(this);
    QString styleSheet2 = "QWidget#fayed { background-image: url(C:/Users/fayed/Desktop/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";

     ui->fayed->setStyleSheet(styleSheet2);

}

quitter::~quitter()
{
    delete ui;
}

void quitter::on_quitter_2_clicked()
{
    close();
}

void quitter::on_rester_clicked()
{
exit(1);
}
