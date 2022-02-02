#include "add_all_music_into_playlist.h"
#include "ui_add_all_music_into_playlist.h"

Add_all_music_into_playlist::Add_all_music_into_playlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_all_music_into_playlist)
{
    ui->setupUi(this);
}

Add_all_music_into_playlist::~Add_all_music_into_playlist()
{
    delete ui;
}
