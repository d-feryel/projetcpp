#include "calculatrice.h"

#include "ui_calculatrice.h"
#include <QDebug>
double firstnum;
bool usertyping= false;

Calculatrice::Calculatrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calculatrice)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digits_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digits_pressed()));
     connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digits_pressed()));
      connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digits_pressed()));
       connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digits_pressed()));
        connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digits_pressed()));
         connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digits_pressed()));
          connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digits_pressed()));
           connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digits_pressed()));
            connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digits_pressed()));
             connect(ui->pushButton_plusmoin,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
             connect(ui->pushButton_percent,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

              connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
              connect(ui->pushButton_moins,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
              connect(ui->pushButton_mult,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
              connect(ui->pushButton_div,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

ui->pushButton_plus->setCheckable(true);
ui->pushButton_moins->setCheckable(true);
ui->pushButton_mult->setCheckable(true);
ui->pushButton_div->setCheckable(true);


}

Calculatrice::~Calculatrice()
{
    delete ui;
}

