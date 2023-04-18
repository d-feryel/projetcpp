#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <recherche.h>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QMediaPlayer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>
#include "stat_combo.h"
#include <QTimer>
#include "camera.h"
#include "quitter.h"





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mon_action();
    void action_timer();

private slots:
    void on_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_modifier_clicked();

    void on_tri_num_clicked();

    void on_tri_prix_clicked();

    void on_tri_date_clicked();

    void on_chercher_num_textChanged(const QString &arg1);

    void on_chercher_prix_textChanged(const QString &arg1);

    void on_pdf_clicked();

    void on_start_clicked();

    void on_pause_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pb_excel_clicked();

    void on_stat_clicked();

    void on_tab_recherche_clicked(const QModelIndex &index);

    void on_Facture_clicked();

    void on_camera_clicked();

    void on_retour_clicked();

    void on_capture2_clicked();

private:
    Ui::MainWindow *ui;
    Recherche R;
private:
    QMediaPlayer*	playermusic;
    QMediaPlayer*	player;
    stat_combo *s;
    int compteur1;
    QTimer *timer;
    camera *c;

};
#endif // MAINWINDOW_H
