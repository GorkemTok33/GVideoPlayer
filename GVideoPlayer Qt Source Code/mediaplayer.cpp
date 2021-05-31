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

#include "mediaplayer.h"

Mediaplayer::Mediaplayer(QWidget *parent)
{
    filePath = new QString();
    filter = new QString();
    isPlay = new bool();
    isMuted = new bool();
    brightness = new int();
    contrast = new int();
    currentposition = new qint64();
    *isPlay = false;
    *isMuted = false;
    *filter = "Video Dosyaları(*.mp4 *.MP4 *.avi *.AVI *.mkv *.MKV *.flv *.FLV *.ts *.TS)";
    this->parent = parent;
    player = new QMediaPlayer(this->parent, QMediaPlayer::VideoSurface);
    plist = new playlist(this->parent,player, filePath, isPlay);
    videoWidget = new myvideowidget(this->parent);
    videoWidget->setStyleSheet("background-color: black");
    player->setVideoOutput(videoWidget);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    *brightness = videoWidget->brightness();
    *contrast = videoWidget->contrast();
    connect(plist, SIGNAL(play_()), this, SLOT(play()));
    connect(videoWidget->actionPlay, &QAction::triggered, this, &Mediaplayer::play);
    connect(videoWidget->actionPause, &QAction::triggered, this, &Mediaplayer::pause);
    connect(videoWidget->actionNext, &QAction::triggered, this, &Mediaplayer::next);
    connect(videoWidget->actionPrev, &QAction::triggered, this, &Mediaplayer::prev);
}

quint64 Mediaplayer::getDuration()
{
    return player->duration();
}

void Mediaplayer::openFile()
{
    *filePath = QFileDialog::getOpenFileName(parent,tr("Açılacak Video Dosyasının Konumunu Seçin"),"c:/", *filter);
    addFileIntoPlaylist(*filePath);
    *isPlay = false;
    *currentposition = 0;
    play();
}

void Mediaplayer::openDropFile(QString path)
{
    *filePath = path;
    *isPlay = false;
    *currentposition = 0;
    play();
}

void Mediaplayer::play()
{
    if(*filePath != "" && !*isPlay)
    {
        try
        {
            player->stop();
            qDebug()<<"play: "<<*filePath;
            player->setMedia(QUrl::fromLocalFile(*filePath));
            player->setPosition(0);
            player->play();
            player->setPosition(*currentposition);
            *brightness = videoWidget->brightness();
            *contrast = videoWidget->contrast();
            *isPlay = true;
        }

        catch(...)
        {
            QMessageBox::warning(parent,"Oynatma Hatası","Bir oynatma hatası ile karşılaşıldı ! Bu hata video dosyasının biçiminin desteklenmemesinden kaynaklanabilir.");
        }
    }

    return;
}

void Mediaplayer::pause()
{
    if(*isPlay)
    {
        try
        {
            *currentposition = player->position();
            player->pause();
            *isPlay = false;
        }
        catch (...)
        {
            QMessageBox::warning(parent,"Durdurma Hatası","Beklenmeyen bir sorun oluştu !");
        }
    }
}

void Mediaplayer::prev()
{
    emit plist->prev_();
    return;
}

void Mediaplayer::next()
{
    emit plist->next_();
    return;
}

void Mediaplayer::mute()
{
    if(*isMuted)
    {
        player->setMuted(false);
        *isMuted = false;
    }

    else
    {
        player->setMuted(true);
        *isMuted = true;
    }
}

void Mediaplayer::upBrightness()
{
    *brightness += 10;
    if(*brightness > 100)
        *brightness = 100;
    videoWidget->setBrightness(*brightness);
}

void Mediaplayer::downBrightness()
{
    *brightness -= 10;
    if(*brightness < -100)
        *brightness = -100;
    videoWidget->setBrightness(*brightness);
}

void Mediaplayer::upContrast()
{
    *contrast += 10;
    if(*contrast > 100)
        *contrast = 100;
    videoWidget->setContrast(*contrast);
}

void Mediaplayer::downContrast()
{
    *contrast -= 10;
    if(*contrast < -100)
        *contrast = -100;
    videoWidget->setContrast(*contrast);
}

QVideoWidget* Mediaplayer::getVideoWidget()
{
    return this->videoWidget;
}

QMediaPlayer *Mediaplayer::getMediaPlayer()
{
    return this->player;
}

bool Mediaplayer::isMuted_()
{
    return *this->isMuted;
}

bool Mediaplayer::isLoadedFromFile()
{
    return plist->isLoadedFromFile();
}

void Mediaplayer::setAutoplay(bool value)
{
    plist->setAutoplay(value);
}

int Mediaplayer::getBrightness()
{
    return *this->brightness;
}

int Mediaplayer::getContrast()
{
    return *this->contrast;
}

void Mediaplayer::addFileIntoPlaylist(QString fileName)
{
    plist->addMediafileAsFilePath(fileName);
    emit newAdded();
}

void Mediaplayer::playFromList(const int index)
{
    plist->playMediafile(index);
}

void Mediaplayer::removeFromPlaylist(int index)
{
    plist->removeMediaFileFromList(index);
    if(plist->getPlayerlist().size() == 0)
        player->stop();
}

int Mediaplayer::getcurrentIndex()
{
    return plist->getCurrentIndex();
}

QVector<QString> Mediaplayer::getplaylist()
{
    return plist->getPlayerlist();
}

QString Mediaplayer::getCurrentName()
{
    return plist->getCurrentMediafile();
}

void Mediaplayer::setRandomPlay(bool value)
{
    plist->setisRandom(value);
}

void Mediaplayer::fullScreen()
{
    videoWidget->exitFullscreen();
}

void Mediaplayer::savePlaylist(const QString &name)
{
    plist->savePlaylist(name);
}

void Mediaplayer::clear()
{
    plist->clear();
}

QString Mediaplayer::loadPlaylist()
{
    return plist->loadPlaylist();
}

QString Mediaplayer::loadPlaylist(const QString &fileName)
{
    return plist->loadPlaylist(fileName);
}

QString Mediaplayer::getPlaylistTitle()
{
    return plist->getPlaylistTitle();
}
