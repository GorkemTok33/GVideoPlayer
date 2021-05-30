/*
****************************************************************************************
****************************************************************************************
Program: GVideoPlayer (Gorkem Video Player)
Publish Date: 06.15.2021
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: Creative Commons License, Copyright 2021 Görkem Tok
****************************************************************************************
****************************************************************************************
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QStyle>
#include <QMainWindow>
#include "mediaplayer.h"
#include "dialog.h"
#include "playlistwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void load();
    void openFile();
    void saveFile();
    void play();
    void pause();
    void next();
    void prev();
    void mute();
    void upb();
    void downb();
    void upc();
    void downc();
    void opacityUp();
    void opacityDown();
    void fullScreen_();


private slots:
    void startCheck();
    void on_actionA_triggered();
    void on_actionFarkl_Kaydet_triggered();
    void on_btnPlay_clicked();
    void on_btnPause_clicked();
    void on_btnNext_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_setSliderValue(qint64  position);
    void on_horizontalSlider_setMaximum(qint64 value);
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_btnFullscreen_clicked();
    void on_btnMute_clicked();
    void on_actionHakk_nda_triggered();
    void on_action_10_triggered();
    void on_action_11_triggered();
    void on_action_12_triggered();
    void on_action_13_triggered();
    void on_actionEn_Boy_Oran_n_nemseme_triggered();
    void on_actionEn_Boy_Oran_n_Koru_triggered();
    void on_actionEn_Boy_Oran_n_Geni_leterek_Koru_triggered();
    void on_actionPlaylist_G_r_nt_le_triggered();
    void on_pushButton_clicked();
    void opacityUp_();
    void opacityDown_();
    void on_action_0_05_Art_r_triggered();
    void on_action_0_05_Azalt_triggered();
    void on_actionPlaylisti_G_r_nt_le_triggered();
    void currentChanged();
    void fullScreen();


private:
    Ui::MainWindow *ui;
    Mediaplayer *mp;
    Dialog *about;
    playlistwindow *plist;
    void initialize();
    void showTime(int);
    void calculateTimeString(int, QString&);
    QString *timedur;
    QString *timepast;
    double *opacity;

};
#endif // MAINWINDOW_H
