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

#ifndef PLAYLISTCHOOSENAME_H
#define PLAYLISTCHOOSENAME_H

#include <QDialog>

namespace Ui {
class PlaylistChooseName;
}

class PlaylistChooseName : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistChooseName(QWidget *parent = nullptr, bool isLoadedFromFile = false, QString name = "Playlistim", int val = 0);
    ~PlaylistChooseName();

signals:
    void savePlaylist_(const QString&, int);

private slots:
    void on_btnSave_clicked();
    void on_lineEditName_textEdited(const QString &arg1);

private:
    Ui::PlaylistChooseName *ui;
    int val;
};

#endif // PLAYLISTCHOOSENAME_H
