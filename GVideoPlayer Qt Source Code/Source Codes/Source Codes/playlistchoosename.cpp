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

#include "playlistchoosename.h"
#include "ui_playlistchoosename.h"

PlaylistChooseName::PlaylistChooseName(QWidget *parent, bool isLoadedFromFile, QString name) :
    QDialog(parent),
    ui(new Ui::PlaylistChooseName)
{
    ui->setupUi(this);

    if(!isLoadedFromFile)
    {
        this->setWindowTitle("Playlist Kaydetme");
    }
    else
    {
        this->setWindowTitle("Playlist İsim Değiştirme");
    }

    ui->lineEditName->setText(name);
}

PlaylistChooseName::~PlaylistChooseName()
{
    delete ui;
}

void PlaylistChooseName::on_btnSave_clicked()
{
    emit savePlaylist_(ui->lineEditName->text());
    this->close();
}

void PlaylistChooseName::on_lineEditName_textEdited(const QString &arg1)
{
    if(arg1.length() == 0)
        ui->btnSave->setEnabled(false);
    else
        ui->btnSave->setEnabled(true);
}
