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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QString *fileName = new QString();
    bool control = true;
    foreach(const QUrl &url, event->mimeData()->urls())
    {
        *fileName = url.toLocalFile();
        if(fileName->contains(".mp4") ||
             fileName->contains(".flv") || fileName->contains(".mkv") || fileName->contains(".wmv") ||
             fileName->contains(".ts") || fileName->contains(".hevc") || fileName->contains(".mov") ||
             fileName->contains(".avchd") || fileName->contains(".webm") || fileName->contains(".MP4") ||
             fileName->contains(".FLV") || fileName->contains(".MKV") || fileName->contains(".WMV") ||
             fileName->contains(".TS") || fileName->contains(".HEVC") || fileName->contains(".MOV") ||
             fileName->contains(".AVCHD") || fileName->contains(".WEBM"))
        {
            if(event->mimeData()->urls().size()==1)
            {
                mp->addFileIntoPlaylist(*fileName);
                mp->openDropFile(*fileName);
                currentChanged();
                this->statusBar()->showMessage("Oynatılıyor: "+*fileName, 0);
                break;
            }

            else
            {
                if(control)
                {
                    mp->openDropFile(*fileName);
                    this->statusBar()->showMessage("Oynatılıyor: "+*fileName, 0);
                    control = false;
                }
                mp->addFileIntoPlaylist(*fileName);
            }
        }

        else if(fileName->contains(".gvp") || fileName->contains(".GVP"))
        {
            if(control)
            {
                mp->loadPlaylist(*fileName);
                control = false;
                break;
            }
        }
    }

    if(!control)
    {
        playlistwindow *playlist = new playlistwindow(this,mp);
        playlist->show();
    }

    free(fileName);
    return;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit fullScreen_();
    }
}

void MainWindow::initialize()
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/icon.png"));
    mp = new Mediaplayer(this);
    ui->horizontalSlider_2->setValue(50);
    connect(this,SIGNAL(load()),this,SLOT(startCheck()));
    connect(this,SIGNAL(openFile()),mp,SLOT(openFile()));
    connect(this,SIGNAL(saveFile()),mp,SLOT(saveFile()));
    connect(this,SIGNAL(play()),mp,SLOT(play()));
    connect(this,SIGNAL(pause()),mp,SLOT(pause()));
    connect(this,SIGNAL(next()),mp,SLOT(next()));
    connect(this,SIGNAL(prev()),mp,SLOT(prev()));
    connect(this,SIGNAL(mute()),mp,SLOT(mute()));
    connect(this,SIGNAL(upb()),mp,SLOT(upBrightness()));
    connect(this,SIGNAL(downb()),mp,SLOT(downBrightness()));
    connect(this,SIGNAL(upc()),mp,SLOT(upContrast()));
    connect(this,SIGNAL(downc()),mp,SLOT(downContrast()));
    connect(this,SIGNAL(opacityUp()),this,SLOT(opacityUp_()));
    connect(this,SIGNAL(opacityDown()),this,SLOT(opacityDown_()));
    connect(this,SIGNAL(fullScreen_()),this,SLOT(fullScreen()));
    connect(mp->getMediaPlayer(),SIGNAL(positionChanged(qint64)), this, SLOT(on_horizontalSlider_setSliderValue(qint64)));
    connect(mp->getMediaPlayer(),SIGNAL(durationChanged(qint64)), this, SLOT(on_horizontalSlider_setMaximum(qint64)));
    connect(mp->getMediaPlayer(),SIGNAL(mediaChanged(const QMediaContent &)),this,SLOT(currentChanged()));
    ui->frame->setStyleSheet("background-color:black;");
    QGridLayout *lay = new QGridLayout(ui->centralwidget);
    lay->addWidget(mp->getVideoWidget());
    ui->frame->setLayout(lay);
    this->setWindowTitle("GVideoPlayer 1.0.0 - Coded by Görkem Tok");
    setAcceptDrops(true);
    timedur = new QString();
    timepast = new QString();
    opacity = new double();
    *opacity = 1.0;
    ui->labelDuration->setText("00.00.00/00.00.00");
    this->statusBar()->showMessage("Oynatmak için dosyayı sürükleyin ya da dosya seçin: ");
}

void MainWindow::showTime(int second)
{
    calculateTimeString(second, *timepast);
    calculateTimeString(mp->getDuration()*0.001, *timedur);
    ui->labelDuration->setText(*timepast+"/"+*timedur);
}

void MainWindow::calculateTimeString(int second, QString &timeString)
{
    timeString = "";
    int h = second / 3600;
    second = second % 3600;
    int min = second / 60;
    second = second % 60;
    if(!(h - h % 10 >= 10))
        timeString +="0"+QString::number(h);
    else
        timeString += QString::number(h);
    timeString +=":";
    if(!(min - min % 10 >= 10))
        timeString +="0"+QString::number(min);
    else
        timeString += QString::number(min);
    timeString +=":";
    if(!(second - second % 10 >= 10))
        timeString +="0"+QString::number(second);
    else
        timeString += QString::number(second);

    return;
}

void MainWindow::on_actionA_triggered()
{
    emit openFile();
}

void MainWindow::on_actionFarkl_Kaydet_triggered()
{
    emit saveFile();
}

void MainWindow::on_btnPlay_clicked()
{
    emit play();
}

void MainWindow::on_btnPause_clicked()
{
    emit pause();
}

void MainWindow::on_btnNext_clicked()
{
    emit next();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    mp->getMediaPlayer()->setPosition(position);
}

void MainWindow::on_horizontalSlider_setSliderValue(qint64 position)
{
    ui->horizontalSlider->setValue(position);
    int second = position*0.001;
    showTime(second);
}

void MainWindow::on_horizontalSlider_setMaximum(qint64 value)
{
    ui->horizontalSlider->setMaximum(value);
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    mp->getMediaPlayer()->setVolume(position);
    ui->lblSound->setText(QString::number(position));
}

void MainWindow::on_btnFullscreen_clicked()
{
    mp->fullScreen();
}

void MainWindow::on_btnMute_clicked()
{
    emit mute();
    if(!mp->isMuted_())
        ui->btnMute->setIcon(QIcon(":/icons/volume-1.png"));
    else
    {
        ui->btnMute->setIcon(QIcon(":/icons/muted.png"));
    }

    return;
}

void MainWindow::on_actionHakk_nda_triggered()
{
    about = new Dialog(this);
    about->show();
}

void MainWindow::on_action_10_triggered()
{
    emit upb();
}

void MainWindow::on_action_11_triggered()
{
    emit downb();
}

void MainWindow::on_action_12_triggered()
{
    emit upc();
}

void MainWindow::on_action_13_triggered()
{
    emit downc();
}

void MainWindow::on_actionEn_Boy_Oran_n_nemseme_triggered()
{
    mp->getVideoWidget()->setAspectRatioMode(Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionEn_Boy_Oran_n_Koru_triggered()
{
    mp->getVideoWidget()->setAspectRatioMode(Qt::KeepAspectRatio);
}

void MainWindow::on_actionEn_Boy_Oran_n_Geni_leterek_Koru_triggered()
{
    mp->getVideoWidget()->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
}

void MainWindow::on_actionPlaylist_G_r_nt_le_triggered()
{
    plist = new playlistwindow(this,mp);
    plist->setModal(false);
    plist->show();
}

void MainWindow::on_pushButton_clicked()
{
    emit prev();
}

void MainWindow::opacityUp_()
{
    *opacity += 0.05;
    if(*opacity > 1.0)
        *opacity = 1.0;
    this->setWindowOpacity(*opacity);
}

void MainWindow::opacityDown_()
{
    *opacity -= 0.05;
    if(*opacity < 0.0)
        *opacity = 0.0;
    this->setWindowOpacity(*opacity);
}

void MainWindow::on_action_0_05_Art_r_triggered()
{
    emit opacityUp();
}

void MainWindow::on_action_0_05_Azalt_triggered()
{
    emit opacityDown();
}

void MainWindow::on_actionPlaylisti_G_r_nt_le_triggered()
{

}

void MainWindow::currentChanged()
{
    this->statusBar()->clearMessage();
    this->statusBar()->showMessage("Oynatılıyor: "+mp->getCurrentName(), 0);
}

void MainWindow::fullScreen()
{

}

void MainWindow::startCheck()
{
    if(QCoreApplication::instance()->arguments().size() > 1)
    {
        QString *fileName = new QString();
        *fileName = QCoreApplication::instance()->arguments().at(1);
        if(fileName->contains(".mp4") ||
            fileName->contains(".flv") || fileName->contains(".mkv") || fileName->contains(".wmv") ||
            fileName->contains(".ts") || fileName->contains(".hevc") || fileName->contains(".mov") ||
            fileName->contains(".avchd") || fileName->contains(".webm") || fileName->contains(".MP4") ||
            fileName->contains(".FLV") || fileName->contains(".MKV") || fileName->contains(".WMV") ||
            fileName->contains(".TS") || fileName->contains(".HEVC") || fileName->contains(".MOV") ||
            fileName->contains(".AVCHD") || fileName->contains(".WEBM"))
        {
            mp->addFileIntoPlaylist(*fileName);
            mp->openDropFile(*fileName);
            currentChanged();
            this->statusBar()->showMessage("Oynatılıyor: "+*fileName, 0);
        }

        else if(fileName->contains(".gvp") || fileName->contains(".GVP"))
        {
            mp->loadPlaylist(*fileName);
            playlistwindow *playlist = new playlistwindow(this,mp);
            playlist->show();
        }
    }
}



