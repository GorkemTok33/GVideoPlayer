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


#include "playlistwindow.h"
#include "ui_playlistwindow.h"

playlistwindow::playlistwindow(QWidget *parent, Mediaplayer *mp) :
    QDialog(parent),
    ui(new Ui::playlistwindow)
{
    ui->setupUi(this);
    this->setWindowTitle("GVideoPlayer - Playlist");
    this->setAcceptDrops(true);
    this->mp = mp;
    oldrow = 0;
    newrow = 0;
    connect(mp->getMediaPlayer(), SIGNAL(mediaChanged(const QMediaContent &)),this, SLOT(mediaChanged()));
    connect(mp, SIGNAL(newAdded()),this,SLOT(newAdded()));
    loadplaylist();
    ui->lblPlaylistName->setText("Playlist Adı: "+mp->getPlaylistTitle());
}

playlistwindow::~playlistwindow()
{
    delete ui;
}

void playlistwindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void playlistwindow::dropEvent(QDropEvent *event)
{
    QString fileName;
    foreach(const QUrl &url, event->mimeData()->urls())
    {
        fileName = url.toLocalFile();
        if(fileName.contains(".mp4") ||
            fileName.contains(".flv") || fileName.contains(".mkv") || fileName.contains(".wmv") ||
            fileName.contains(".ts") || fileName.contains(".hevc") || fileName.contains(".mov") ||
            fileName.contains(".avchd") || fileName.contains(".webm") || fileName.contains(".MP4") ||
            fileName.contains(".FLV") || fileName.contains(".MKV") || fileName.contains(".WMV") ||
            fileName.contains(".TS") || fileName.contains(".HEVC") || fileName.contains(".MOV") ||
            fileName.contains(".AVCHD") || fileName.contains(".WEBM"))
        {
            if(event->mimeData()->urls().size()==1)
            {
                mp->addFileIntoPlaylist(fileName);
                break;
            }

            else
            {
                mp->addFileIntoPlaylist(fileName);
            }
        }

        else if(fileName.contains(".gvp") || fileName.contains(".GVP"))
        {
            ui->lblPlaylistName->setText("Playlist Adı: "+mp->loadPlaylist(fileName));
            loadplaylist();
            break;
        }
    }
    updateListView();
    return;
}

void playlistwindow::updateListView()
{
    ui->playListWidget->clear();

    foreach(const QString fileName, mp->getplaylist())
    {
        QFile file(fileName);
        QFileInfo fileinfo(fileName);
        QListWidgetItem *item = new QListWidgetItem(fileinfo.fileName());
        item->setForeground(Qt::lightGray);
        ui->playListWidget->addItem(item);
    }

    if(mp->getplaylist().size() > 0)
    {
        mp->playFromList(mp->getcurrentIndex());
    }

    else
        ui->lblplaytitle->setText("--");
    return;
}

void playlistwindow::loadplaylist()
{
    if(mp->getplaylist().size() > 0)
    {
        foreach(const QString fileName, mp->getplaylist())
        {
            QFile file(fileName);
            QFileInfo fileinfo(fileName);
            QListWidgetItem *item = new QListWidgetItem(fileinfo.fileName());
            item->setForeground(Qt::lightGray);
            ui->playListWidget->addItem(item);
        }

        newrow = mp->getcurrentIndex();
        ui->playListWidget->item(newrow)->setForeground(Qt::white);
        ui->lblplaytitle->setText(ui->playListWidget->item(newrow)->text());
    }

    else
      ui->lblplaytitle->setText("--");
}

void playlistwindow::on_playListWidget_itemDoubleClicked(QListWidgetItem *item)
{
     oldrow = newrow;
     newrow = ui->playListWidget->currentIndex().row();
     if(ui->playListWidget->item(oldrow) != nullptr)
         ui->playListWidget->item(oldrow)->setForeground(Qt::lightGray);
     mp->playFromList(ui->playListWidget->currentIndex().row());
     ui->lblplaytitle->setText(ui->playListWidget->item(newrow)->text());
}

void playlistwindow::on_cbAutoplay_clicked()
{
    if(ui->cbAutoplay->isChecked())
    {
        mp->setAutoplay(true);
        return;
    }

    mp->setAutoplay(false);
    return;
}

void playlistwindow::on_btnAdd_clicked()
{
    QStringList Selectedfiles = QFileDialog::getOpenFileNames(this,tr("Açılacak Video Dosyasının Konumunu Seçin"),"c:/", "Video Dosyaları(*.mp4 *.MP4 *.avi *.AVI *.mkv *.MKV *.flv *.FLV *.ts *.TS)");
    foreach(QString name, Selectedfiles)
    {
        mp->addFileIntoPlaylist(name);
    }
    updateListView();
    return;
}

void playlistwindow::on_btnRemove_clicked()
{
    if(mp->getplaylist().size() >= 0)
    {
        if(mp->getcurrentIndex() == ui->playListWidget->currentIndex().row())
        {
            if(mp->getcurrentIndex()-1 != 0)
                mp->playFromList(mp->getcurrentIndex()-1);
        }
        mp->removeFromPlaylist(ui->playListWidget->currentIndex().row());
        updateListView();
        mediaChanged();
    }
}

void playlistwindow::mediaChanged()
{
    oldrow = newrow;
    newrow = mp->getcurrentIndex();
    if(ui->playListWidget->item(oldrow) != nullptr)
         ui->playListWidget->item(oldrow)->setForeground(Qt::lightGray);
    if(ui->playListWidget->item(newrow) != nullptr)
    {
        ui->playListWidget->item(newrow)->setForeground(Qt::white);
        ui->playListWidget->setCurrentRow(newrow);
        ui->lblplaytitle->setText(ui->playListWidget->item(newrow)->text());
    }
}

void playlistwindow::on_cbRandomplay_clicked()
{
    mp->setRandomPlay(ui->cbRandomplay->isChecked());
}

void playlistwindow::newAdded()
{
    updateListView();
    ui->playListWidget->item(mp->getcurrentIndex())->setForeground(Qt::white);
    ui->playListWidget->item(mp->getcurrentIndex())->setSelected(true);
}

void playlistwindow::on_pushButtonSavePlaylist_clicked()
{
    playlistchoosename = new PlaylistChooseName(this);
    connect(playlistchoosename, SIGNAL(savePlaylist_(const QString &)),this,SLOT(savePlaylist(const QString &)));
    playlistchoosename->show();
}

void playlistwindow::on_pushButtonPlaylistOpen_clicked()
{
    mp->clear();
    ui->playListWidget->clear();
    ui->lblPlaylistName->setText("Playlist Adı: "+(mp->loadPlaylist()== "loadERROR" ? "Varsayılan Playlist":mp->getPlaylistTitle()));
    loadplaylist();
}

void playlistwindow::savePlaylist(const QString &name)
{
    mp->savePlaylist(name);
    ui->lblPlaylistName->setText(mp->getPlaylistTitle());
}

void playlistwindow::on_btnChangeListname_clicked()
{
    if(!mp->isLoadedFromFile())
    {
        QMessageBox::information(this,"Playlist Yüklenmemiş","Playlist ismini değiştirebilmeniz için playlist yüklenmiş olmalıdır !");
        return;
    }
    playlistchoosename = new PlaylistChooseName(this, mp->isLoadedFromFile(), mp->getPlaylistTitle());
    connect(playlistchoosename, SIGNAL(savePlaylist_(const QString &)),this,SLOT(savePlaylist(const QString &)));
    playlistchoosename->show();
}

void playlistwindow::on_pushButton_clicked()
{
    mp->clear();
    ui->playListWidget->clear();
    loadplaylist();
    ui->lblPlaylistName->setText("Playlist Adı: Varsayılan Playlist");
}
