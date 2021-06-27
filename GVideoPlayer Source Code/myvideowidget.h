/*
****************************************************************************************
****************************************************************************************
Program: GVideoPlayer (Gorkem Video Player)
Publish Date: 06.27.2021
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: Creative Commons License, Copyright 2021 Görkem Tok
****************************************************************************************
****************************************************************************************
*/

#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QMediaPlayer>
#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QVideoWidget>
#include <QPainter>
#include <QPushButton>
#include <QMenu>
#include <QAction>

class myvideowidget : public QVideoWidget
{
public:
    myvideowidget(QWidget *parent = nullptr):QVideoWidget(parent)
            {
                createActions();
            };

    QAction *actionPlay;
    QAction *actionPause;
    QAction *actionFullscreen;
    QAction *actionNext;
    QAction *actionPrev;
    QAction *Aspectratio1;
    QAction *Aspectratio2;
    QAction *Aspectratio3;

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);

public slots:
    void exitFullscreen();
    void asp1();
    void asp2();
    void asp3();

private:
    void createActions();
    void createMenu(QContextMenuEvent *event);
    bool isFullscreen = false;

};

#endif // MYVIDEOWIDGET_H
