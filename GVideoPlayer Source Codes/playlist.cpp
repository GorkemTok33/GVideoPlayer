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

#include "playlist.h"

playlist::playlist()
{

}

playlist::playlist(QWidget *parent, QMediaPlayer *mp, QString *filePath, bool *isPlay)
{
    this->parent = parent;
    this->mp = mp;
    this->playerfilePath = filePath;
    this->isPlay = isPlay;
    init();
    qDebug()<<"class playlist contructor";
}

void playlist::addMediafileAsFilePath(const QString &filepath)
{
    files->push_back(filepath);
    *currentMediafile = files->at(0);
    *playerfilePath = *currentMediafile;
    qDebug()<<"addMediafileAsFilePath: "+filepath;
}

void playlist::addMediafilesAsFilePath(const QVector<QString> &files)
{
    foreach(QString fileN, files)
        this->files->push_back(fileN);
    qDebug()<<"addMediafileAsFilePath: files added!";
}

void playlist::removeMediaFileFromList(const QString fileName)
{
    if(files->removeOne(fileName))
        qDebug()<<"removeMediaFileFromList: "+fileName+" removed!";
    else
        qDebug()<<"removeMediaFileFromList: "+fileName+" not in list!";
}

void playlist::removeMediaFileFromList(int index)
{
    if(index >= 0 && index < files->size())
    {
        files->removeAt(index);
        qDebug()<<"removeMediaFileFromList: "+QString::number(index)+" removed!";
        return;
    }

    qDebug()<<"removeMediaFileFromList: "+QString::number(index)+" not in list!";
    return;
}

QString playlist::getNextFileName()
{
    if(*currentIndex == files->size()-1)
        return files->at(0);

    return files->at(*currentIndex+1);
}

QString playlist::getPrevFileName()
{
    if(*currentIndex == 0)
        return files->at(files->size()-1);

    return files->at(*currentIndex-1);
}

void playlist::setPlaylist(QVector<QString> &files)
{
    this->files->clear();
    this->files->append(files);
    qDebug()<<"setPlaylist: successful!";
}

void playlist::setReplayTimes(int times)
{
    *this->times = times;
}

void playlist::playMediafile(const int index)
{
    if(index >= 0 && index < files->size())
    {
        *currentIndex = index;
        qDebug()<<"index: "<<*currentIndex;
        *currentMediafile = this->files->at(*currentIndex);
        emit play_();
        qDebug()<<"playMediafile: playing "+*currentMediafile;
        return;
    }

    qDebug()<<"playMediafile: Exception: out of file list!";
    return;
}

void playlist::playMediaFile(QString fileName)
{

    return;
}

QVector<QString> playlist::getPlayerlist()
{
    return *files;
}

QString playlist::getCurrentMediafile()
{
    return *currentMediafile;
}

int playlist::getCurrentIndex()
{
    return *currentIndex;
}

void playlist::setAutoplay(bool status)
{
    *isAutoplay = status;
}

bool playlist::isAutoplay_()
{
    return *isAutoplay;
}

bool playlist::isLoadedFromFile()
{
    return *isListloadedfromFile;
}

void playlist::setCurrentDuration(qint64 duration)
{
    *currentDuration = duration;
}

void playlist::setisPlay(bool value)
{
    *isPlay = value;
}

void playlist::setisRandom(bool value)
{
    *isRandom = value;
}

void playlist::play()
{
    *currentDuration = 500;
    if(*currentMediafile != "" && *currentMediafile != NULL)
    {
        *isPlay = false;
        *playerfilePath = *currentMediafile;
        qDebug()<<"current: "<<*playerfilePath;
        return;
    }

    return;
}

void playlist::replay()
{
    if(mp->isVideoAvailable())
    {
        mp->setPosition(0);
        mp->play();
        return;
    }
}

void playlist::next()
{
    if(files->size() > 0)
    {
        if(*currentIndex < files->size()-1)
            *currentIndex = *currentIndex + 1;

        else
            *currentIndex = 0;

        *currentMediafile = files->at(*currentIndex);
        emit play_();
    }
}

void playlist::prev()
{
    if(files->size() > 0)
    {
        if(*currentIndex > 0)
            *currentIndex-=1;

        else
            *currentIndex = files->size()-1;

        *currentMediafile = files->at(*currentIndex);
        emit play_();
    }
}

void playlist::savePlaylist(const QString &name)
{
    QString filter = "GVideoPlayer playlist dosyası (*.gvp)";
    QString filePath = "";
    if(!*isListloadedfromFile)
       filePath = QFileDialog::getSaveFileName(parent,tr("Playlistin Kayıt Edileceği Konumu Seçin"),"c:/Playlist1.gvp", filter);
    else
        filePath = *playlistPath;

    if(filePath != "" && filePath != NULL)
    {
        QFile *file = new QFile(filePath);
        if(file->open(QFile::WriteOnly))
        {
            QTextStream *stream = new QTextStream();
            stream->setDevice(file);
            *stream<<name<<"\n";
            for(int i = 0; i<files->size(); i++)
            {
                *stream<<files->at(i).toUtf8()<<"\n";
            }
            file->flush();
            file->close();
            *playlistTitle = name;
        }
    }
}

QString playlist::loadPlaylist()
{
    QString filter = "GVideoPlayer Playlist Dosyası (*.gvp)";
    QString filePath = QFileDialog::getOpenFileName(parent,tr("Playlistin yükleneceği dosyayı seçin"),"c:/", filter);
    QString readedfile = "";
    QString name = "";
    if(filePath != "" && filePath != NULL)
    {
        QFile *file = new QFile(filePath);
        if(file->open(QFile::ReadOnly | QIODevice::Text))
        {
            QTextStream *stream = new QTextStream();
            stream->setDevice(file);
            name = stream->readLine();
            while(!stream->atEnd())
            {
                readedfile = stream->readLine();
                addMediafileAsFilePath(readedfile);
            }

            file->close();
        }
        free(file);
        *playlistPath = filePath;
        *isListloadedfromFile = true;
        return name;
    }

    return "loadERROR";
}

QString playlist::loadPlaylist(const QString &fileName)
{
    *playlistPath = fileName;
    QString readedfile = "";
    if(*playlistPath != "" && *playlistPath != NULL)
    {
        QFile *file = new QFile(*playlistPath);
        if(file->open(QFile::ReadOnly | QIODevice::Text))
        {
            QTextStream *stream = new QTextStream();
            stream->setDevice(file);
            *playlistTitle = stream->readLine();
            while(!stream->atEnd())
            {
                readedfile = stream->readLine();
                addMediafileAsFilePath(readedfile);
            }

            file->close();
        }
        free(file);
        *isListloadedfromFile = true;
        *playlistPath = fileName;
        return *playlistTitle;
    }

    return "loadERROR";
}

QString playlist::getPlaylistTitle()
{
    return *playlistTitle;
}

void playlist::positionCheck(qint64 position)
{
    if(position*0.001 == *currentDuration*0.001 && position*0.001 != 0)
    {
        if(*isAutoplay)
        {
            if(*isRandom)
                random();

            else
                emit next_();
        }

        else
        {
            mp->setPosition(0);
            *isPlay = false;
        }
    }

}

void playlist::durationChanged(qint64 duration)
{
    mutex->lock();
    *currentDuration = duration;
    mutex->unlock();
}

void playlist::init()
{
    playlistPath = new QString();
    playlistTitle = new QString();
    files = new QVector<QString>();
    times = new int();
    currentIndex = new int();
    currentDuration = new qint64();
    currentMediafile = new QString();
    isAutoplay = new bool();
    isRandom = new bool();
    isListloadedfromFile = new bool();
    *isAutoplay = true;
    *isRandom = false;
    *isListloadedfromFile = false;
    *currentIndex = 0;
    *currentDuration = 500;
    *currentMediafile = "";
    *playlistTitle = "Playlist Adı: Varsayılan Playlist";
    mutex = new QMutex();
    connect(this, SIGNAL(play_()), this, SLOT(play()));
    connect(this, SIGNAL(replay_()), this, SLOT(replay()));
    connect(this, SIGNAL(next_()), this, SLOT(next()));
    connect(this, SIGNAL(prev_()), this, SLOT(prev()));
    connect(mp,SIGNAL(positionChanged(qint64)), this, SLOT(positionCheck(qint64)));
    connect(mp,SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
}

void playlist::random()
{
    if(files->size() > 0)
    {
        *currentIndex = qrand() % ((files->size()) - 0) + 0;
        *currentMediafile = files->at(*currentIndex);
        emit play_();
    }

    return;
}

void playlist::clear()
{
    files->clear();
    *isListloadedfromFile = false;
    *playlistPath = "";
    *currentIndex = 0;
    *currentDuration = 500;
    *currentMediafile = "";
}
