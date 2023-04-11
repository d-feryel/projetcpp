#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employe.h"
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();


    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);



    void on_capture_clicked();

    void on_pushButton_5_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_stat_clicked();

    void on_pushButton_6_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::MainWindow *ui;
   Employe Etmp;
   QTcpSocket*mSocket;
  stat_combo * s;
  chat * c;
   chat * c1;


};
#endif // MAINWINDOW_H
