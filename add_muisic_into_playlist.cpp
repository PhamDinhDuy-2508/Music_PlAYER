#include "add_muisic_into_playlist.h"
#include "ui_add_muisic_into_playlist.h"

Add_muisic_into_Playlist::Add_muisic_into_Playlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_muisic_into_Playlist)
{
    ui->setupUi(this);
}

Add_muisic_into_Playlist::~Add_muisic_into_Playlist()
{
    delete ui;
}
