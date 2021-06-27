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

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QDebug>
#include <QtCore>
#include <QObject>
#include <QVector>
#include <QMediaPlayer>
#include <QListWidget>
#include <QMutex>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QStringList>

class playlist:public QObject
{
    Q_OBJECT
public:
    playlist();
    playlist(QWidget *parent, QMediaPlayer *mp, QString *filePath, bool *isPlay);
    void addMediafileAsFilePath(const QString &filepath);
    void addMediafilesAsFilePath(const QVector<QString> &files);
    void removeMediaFileFromList(const QString fileName);
    void removeMediaFileFromList(int index);
    void setPlaylist(QVector<QString> &files);
    void setReplayTimes(int times);
    void playMediafile(const int index);
    void playMediaFile(QString fileName);
    void setCurrentDuration(qint64 duration);
    void setisPlay(bool value);
    void setisRandom(bool value);
    void savePlaylist(const QString &name, int val);
    void clear();
    void setAutoplay(bool status);
    int getCurrentIndex();
    bool isAutoplay_();
    bool isLoadedFromFile();
    QVector<QString> getPlayerlist();
    QString getNextFileName();
    QString getPrevFileName();
    QString getCurrentMediafile(); 
    QString loadPlaylist();
    QString loadPlaylist(const QString &name);
    QString getPlaylistTitle();

signals:
    void play_();
    void replay_();
    void next_();
    void prev_();

public slots:
    void play();
    void replay();
    void next();
    void prev();

private slots:
    void positionCheck(qint64 position);
    void durationChanged(qint64 duration);

private:
    void init();
    void random();
    QWidget *parent;
    QFile *file;
    QMediaPlayer *mp;
    QVector<QString> *files;
    qint64 *currentDuration;
    QString *currentMediafile;
    QString *playerfilePath;
    QString *playlistPath;
    QString *playlistTitle;
    QMutex *mutex;
    QListWidget *listWidget;
    int *times;
    int *currentIndex;
    bool *isAutoplay;
    bool *isPlay;
    bool *isRandom;
    bool *isListloadedfromFile;

};

#endif // PLAYLIST_H
