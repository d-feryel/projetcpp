#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "equipement.h"
#include"employe.h"
#include <QMainWindow>
#include <stat_combo.h>
#include <QPlainTextEdit>
#include <QPrinter>
//#include <QPrinterInfo>
//#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <stat_combo.h>
#include <chat.h>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();

    void on_supp_eq_clicked();

    void on_modif_eq_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_triref_clicked();

    void on_triprix_clicked();

    void on_triqant_clicked();

    void on_exp_pdf_clicked();

    void on_stat_clicked();

    void on_recher_textChanged(const QString &arg1);




    void on_his_but_clicked();

    void on_histo_activated(const QModelIndex &index);

    void on_aff_clicked();

    void on_listView_activated(const QModelIndex &index);

    void on_typehistorique_2_currentIndexChanged(const QString &arg1);

    void on_suphis_clicked();

    void on_pushButton_clicked();
    ///////////////////////TAKWA///////////////////

    void on_supp_emp_clicked();

    void on_modif_emp_clicked();

    void on_reset_emp_clicked();

    void on_tableView_emp_clicked(const QModelIndex &index);

    void on_tableView_emp_doubleClicked(const QModelIndex &index);

    void on_capture_emp_clicked();

    void on_pdf_emp_clicked();

    void on_radio_nom_emp_clicked();

    void on_radio_cin_emp_clicked();

    void on_rechercher_emp_textChanged(const QString &arg1);

    void on_stat_emp_clicked();

    void on_chat_emp_clicked();

    void on_radio_num_emp_clicked();

private:
    Ui::MainWindow *ui;
    equipement ep;
    stat_combo * st;
    Employe Etmp;
    QTcpSocket*mSocket;
   stat_combo * s;
   /*chat * c;
    chat * c1;*/
};


#endif // MAINWINDOW_H
