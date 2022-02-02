QT       += core gui multimedia
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets


CONFIG += c++11
#LIBS += "E:\QT5\build-Music_Player-Desktop_Qt_5_9_9_MSVC2017_64bit-Release\release\MediaInfo_InfoTip.dll.bak"
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_muisic_into_playlist.cpp \
    create_name_of_table.cpp \
    create_playlist.cpp \
    database_process.cpp \
    file_process.cpp \
    list_mp3.cpp \
    main.cpp \
    mainwindow.cpp \
    music_playlist_choice.cpp \
    nofication_close.cpp \
    proccesing_file_mp3.cpp \
    process_bar.cpp \
    sort_custom.cpp \
    teast.cpp

HEADERS += \
    add_muisic_into_playlist.h \
    create_name_of_table.h \
    create_playlist.h \
    database_process.h \
    file_process.h \
    list_mp3.h \
    mainwindow.h \
    music_playlist_choice.h \
    nofication_close.h \
    proccesing_file_mp3.h \
    process_bar.h \
    sort_custom.h \
    teast.h

FORMS += \
    add_muisic_into_playlist.ui \
    create_name_of_table.ui \
    create_playlist.ui \
    mainwindow.ui \
    music_playlist_choice.ui \
    nofication_close.ui \
    process_bar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
win32: LIBS += -LC:/Users/a/Desktop/lib/ -llibmysql
DISTFILES += \
    Music_Playlist_UI_FILE.qml \
    Music_Playlist_UI_FILEForm.ui.qml

RESOURCES += \
    qml.qrc
