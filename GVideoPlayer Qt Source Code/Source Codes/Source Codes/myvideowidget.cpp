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

#include "myvideowidget.h"


void myvideowidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    exitFullscreen();
}

void myvideowidget::paintEvent(QPaintEvent *event)
{

}

void myvideowidget::contextMenuEvent(QContextMenuEvent *event)
{
    createMenu(event);
}

void myvideowidget::exitFullscreen()
{
    if(isFullscreen)
    {
        this->setFullScreen(false);
        isFullscreen = false;
        return;
    }

    this->setFullScreen(true);
    isFullscreen = true;
    return;
}

void myvideowidget::asp1()
{
    this->setAspectRatioMode(Qt::IgnoreAspectRatio);
    Aspectratio1->setChecked(true);
}

void myvideowidget::asp2()
{
    this->setAspectRatioMode(Qt::KeepAspectRatio);
    Aspectratio2->setChecked(true);
}

void myvideowidget::asp3()
{
    this->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    Aspectratio3->setChecked(true);
}

void myvideowidget::createActions()
{
    actionPlay = new QAction(tr("&   Oynat"), this);
    actionPlay->setIcon(QIcon(":/icons/play.png"));
    actionPlay->setStatusTip(tr("Videoyu oynat/oynatmaya devam et"));

    actionPause = new QAction(tr("&   Durdur"), this);
    actionPause->setIcon(QIcon(":/icons/pause.png"));
    actionPause->setStatusTip(tr("Videoyu oynatmayı durdur"));

    actionFullscreen = new QAction(tr("&   Tam Ekran Yap/Çık"), this);
    actionFullscreen->setIcon(QIcon(":/icons/full-screen.png"));
    actionFullscreen->setStatusTip(tr("Videoyu tam ekran yap/ tam ekrandan çık"));
    connect(actionFullscreen, &QAction::triggered, this, &myvideowidget::exitFullscreen);

    actionNext = new QAction(tr("&   Sonraki Video"), this);
    actionNext->setIcon(QIcon(":/icons/next.png"));
    actionNext->setStatusTip(tr("Sonraki videoyu oynatır"));

    actionPrev = new QAction(tr("&   Önceki Video"), this);
    actionPrev->setIcon(QIcon(":/icons/previous-1.png"));
    actionPrev->setStatusTip(tr("Önceki videoyu oynatır"));

    Aspectratio1 = new QAction(tr("&   En-boy oranını önemseme"), this);
    Aspectratio1->setIcon(QIcon(":/icons/frame.png"));
    connect(Aspectratio1, &QAction::triggered, this, &myvideowidget::asp1);

    Aspectratio2 = new QAction(tr("&   En-boy oranını koru"), this);
    Aspectratio2->setIcon(QIcon(":/icons/frame.png"));
    connect(Aspectratio2, &QAction::triggered, this, &myvideowidget::asp2);

    Aspectratio3 = new QAction(tr("&   En-boy oranını genişleterek koru"), this);
    Aspectratio3->setIcon(QIcon(":/icons/frame.png"));
    connect(Aspectratio3, &QAction::triggered, this, &myvideowidget::asp3);

}

void myvideowidget::createMenu(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(actionPlay);
    menu.addAction(actionPause);
    menu.addAction(actionNext);
    menu.addAction(actionPrev);
    menu.addAction(Aspectratio1);
    menu.addAction(Aspectratio2);
    menu.addAction(Aspectratio3);
    menu.addAction(actionFullscreen);
    menu.exec(event->globalPos());
}
