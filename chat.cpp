#include "chat.h"
#include "ui_chat.h"
#include <QTcpSocket>
#include <QTextStream>
#include "dumessengerconnectiondialog.h"
chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    mSocket =  new QTcpSocket(this);
       connect(mSocket,&QTcpSocket::readyRead, [&](){
           QTextStream T(mSocket);
           auto text = T.readAll();
           ui->textEdit->append(text);

       });
}

chat::~chat()
{
    delete ui;
}

void chat::on_send_clicked()
{
    QTextStream T(mSocket);
    T << ui->nickname->text()<<": "<< ui->message->text();
    mSocket->flush();
    ui->message->clear();
}

void chat::on_bind_clicked()
{
   DuMessengerConnectionDialog D(this);

      if(D.exec() == QDialog::Rejected ){
          return ;
      }
      mSocket->connectToHost( D.hostname() ,  D.port());
}
