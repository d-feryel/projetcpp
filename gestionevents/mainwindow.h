#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <evenement.h>
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
    void on_pb_ajouter_clicked();
    void on_pb_supp_event_clicked();
    void on_pb_modify_clicked();

    void on_search_clicked();

    void on_le_chercher_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_search2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_Stats_clicked();

    void on_tab_events_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_tab_events_2_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Evenement E;
    Evenement Etmp;
};
#endif // MAINWINDOW_H
