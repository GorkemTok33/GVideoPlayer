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

#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile *file = new QFile(":/Style/styleMaterialdark.style");
    QString *path;
    if(file->open(QFile::ReadOnly))
    {
         path = new QString();
         *path = QLatin1String(file->readAll());
         w.setStyleSheet(*path);
         free(path);
    }
    free(file);
    QSize size = qApp->screens()[0]->size();
    QSize wSize;
    if(size.width() >= 1600 && size.height() >= 700)
        wSize = QSize(1320,800);
    else if(size.width() >= 1200 && size.height() >= 700)
        wSize = QSize(850,500);
    w.resize(wSize);
    w.setGeometry
        (
            QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            qApp->desktop()->availableGeometry()
            )
        );
    w.show();
    emit w.load();
    return a.exec();
}
