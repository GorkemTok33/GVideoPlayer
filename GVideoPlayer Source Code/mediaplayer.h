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

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QDebug>
#include <QMediaPlayer>
#include "myvideowidget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidget>
#include "playlist.h"

class Mediaplayer:public QObject
{
    Q_OBJECT
public:
    Mediaplayer(QWidget *parent);
    quint64 getDuration();
    QVideoWidget* getVideoWidget();
    QMediaPlayer* getMediaPlayer();
    bool isMuted_();
    bool isLoadedFromFile();
    void setAutoplay(bool value);
    int getBrightness();
    int getContrast();
    void addFileIntoPlaylist(QString);
    void playFromList(const int index);
    void removeFromPlaylist(int index);
    int getcurrentIndex();
    QVector<QString> getplaylist();
    QString getCurrentName();
    void setRandomPlay(bool value);
    void fullScreen();
    void savePlaylist(const QString &name, int val);
    void clear();
    QString loadPlaylist();
    QString loadPlaylist(const QString &fileName);
    QString getPlaylistTitle();

signals:
    void newAdded();

public slots:
    void openFile();
    void openDropFile(QString path);
    void play();
    void pause();
    void prev();
    void next();
    void mute();
    void upBrightness();
    void upContrast();
    void downBrightness();
    void downContrast();

private:
    QMediaPlayer *player;
    playlist *plist;
    myvideowidget *videoWidget;
    QString *filePath;
    QString *filter;
    qint64 *currentposition;
    int *brightness;
    int *contrast;
    QWidget *parent;
    bool *isPlay;
    bool *isMuted;
};

#endif // MEDIAPLAYER_H
