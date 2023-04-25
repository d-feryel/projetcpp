#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clients.h"
#include <QPrinter>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QTextDocument>
#include "arduino.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajout_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_pdf_clicked();


    void on_tri_clicked();

    void on_pdf_3_clicked();

    void on_chercher_num_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_tab_client_activated(const QModelIndex &index);

    void on_tri_cin_clicked();

    void on_photo_clicked();
    void on_tri_Nom_clicked();

    void on_tri_2_clicked();


    void on_pushButton_3_clicked();

    void addGasState();

    void sendSMS(QString account_sid, QString auth_token, QString message, QString from_number, QString to_number, QString picture_url, bool verbose);

private:
    Ui::MainWindow *ui;
    Clients c;
    Arduino A;
    QByteArray data;
};
#endif // MAINWINDOW_H
