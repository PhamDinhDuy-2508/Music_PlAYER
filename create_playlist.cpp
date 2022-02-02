#include "create_playlist.h"
#include "ui_create_playlist.h"
#include<QMessageBox>
Create_playlist::Create_playlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_playlist)
{
    ui->setupUi(this);
}

Create_playlist::~Create_playlist()
{
    delete ui;
}

QString Create_playlist::get_name_table()
{
    if(ui->lineEdit->text()==""){
        int ret = QMessageBox::warning(this, tr("My Application"),
                                        tr("Name of playlist is invalid"
                                           "Do you want to save your changes?"),
                                         QMessageBox::Cancel);
    }
    else {
        return ui->lineEdit->text() ;
    }
}

void Create_playlist::on_pushButton_clicked()
{
    accept() ;
}
