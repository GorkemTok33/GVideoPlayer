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

#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H

#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <QList>
#include <QListWidgetItem>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QVector>
#include <QStringList>
#include <QMutex>
#include "mediaplayer.h"
#include "playlistchoosename.h"

namespace Ui {
class playlistwindow;
}

class playlistwindow : public QDialog
{
    Q_OBJECT

public:
    explicit playlistwindow(QWidget *parent = nullptr, Mediaplayer *mp = nullptr);
    ~playlistwindow();

protected:
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);

signals:
    void play();
    void pause();
    void next();
    void prev();

private slots:
    void on_playListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_cbAutoplay_clicked();
    void on_btnAdd_clicked();
    void on_btnRemove_clicked();
    void mediaChanged();
    void on_cbRandomplay_clicked();
    void newAdded();
    void on_pushButtonSavePlaylist_clicked();
    void on_pushButtonPlaylistOpen_clicked();
    void savePlaylist(const QString&,int);
    void on_btnChangeListname_clicked();
    void on_pushButton_clicked();

private:
    Ui::playlistwindow *ui;
    Mediaplayer *mp;
    PlaylistChooseName *playlistchoosename;
    void updateListView();
    void loadplaylist();
    int oldrow;
    int newrow;
};

#endif // PLAYLISTWINDOW_H
