QT       += core gui
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += -L"$$PWD/Qt5Core.dll"
LIBS += -L"$$PWD/Qt5Gui.dll"
LIBS += -L"$$PWD/Qt5Multimedia.dll"
LIBS += -L"$$PWD/Qt5MultimediaWidgets.dll"
LIBS += -L"$$PWD/Qt5Network.dll"
LIBS += -L"$$PWD/Qt5OpenGL.dll"
LIBS += -L"$$PWD/Qt5Widgets.dll"
LIBS += -L"$$PWD/msvcp120.dll"
LIBS += -L"$$PWD/msvcr120.dll"

RC_FILE = myapp.rc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mediaplayer.cpp \
    myvideowidget.cpp \
    playlist.cpp \
    playlistchoosename.cpp \
    playlistwindow.cpp \
    start.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    mediaplayer.h \
    myvideowidget.h \
    playlist.h \
    playlistchoosename.h \
    playlistwindow.h \
    start.h \
    version.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    playlistchoosename.ui \
    playlistwindow.ui \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data.qrc

DISTFILES += \
    icon.ico \
    myapp.rc

