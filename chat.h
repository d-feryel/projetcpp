#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include<QTcpSocket>
namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = nullptr);
    ~chat();

private slots:
    void on_send_clicked();

    void on_bind_clicked();

private:
    Ui::chat *ui;
     QTcpSocket *mSocket ;
};

#endif // CHAT_H
