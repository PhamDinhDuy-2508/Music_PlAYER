#include "nofication_close.h"
#include "ui_nofication_close.h"
#include"QPixmap"
#include"QPalette"
#include"QStringList"
#include"QFileDialog"
#include"QStandardPaths"
#include"QDebug"
#include"QFileSystemWatcher"
#include"QDir"
#include"fstream"
#include"iostream"
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <QFile>
#include <QStringList>
#include"future"
#include"proccesing_file_mp3.h"
#include<thread>
#include<vector>
#include<QThread>
#include<process_bar.h>
#include<QVariant>
Nofication_close::Nofication_close(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nofication_close)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Music Player")  ;
    Set_page() ;
}
Nofication_close::Nofication_close(QWidget *parent , QVector<Infomation *> iNFOMATION , QSet<QString> List) :
    QDialog(parent),Infomation_list(iNFOMATION),List_Path(List),
    ui(new Ui::Nofication_close)  
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Music Player")  ;
    Default_path =  "E:/Music" ;
    Set_page() ;
    Procss->Set_Size(iNFOMATION.size())     ;
    connect(this , SIGNAL(Data_change(double)) ,Procss ,  SLOT(percent_change(double))) ;
}
Nofication_close::~Nofication_close()
{
    Thread1->quit() ;
    Thread1->wait() ;
    delete ui;
}
void Nofication_close::Set_page()
{
    QPixmap background("E:/dowload/color-background.png") ;
    background.scaled(this->size() ,Qt::IgnoreAspectRatio) ;
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}
void Nofication_close::Set_Mode(){        
        for(auto x : List_Path) {
            this->Save_Mode(x,name_path_save) ;
        }
        return ;
}
void Nofication_close::Save_Mode(QString src , QString dst)
{
        QDir dir(src);
        if (! dir.exists()){
            return;
        }
        for(auto x :dir.entryList(QDir::Files)) {
            Thread_Process.emplace_back([this , x , src ,  dst  ](){
               QFile::copy(src + QDir::separator() + x, dst + QDir::separator() + x);
            }) ;
        }
        for(auto &x : Thread_Process){
            x.join() ;
            count ++ ;
            emit this->Data_change((count)) ;
        }
    return ;
}
void Nofication_close::Create_Folder()
{
    file_save  = QFileDialog::getSaveFileName(0 ,"Save File"  , Default_path ,  tr("Folder ;;All Files (*)"));
    if(file_save==""){
         name_path_save  = Default_path+Date;
        QDir dir(name_path_save);
        if (!dir.exists()){
          dir.mkdir(".");
        }
    }
    else {
      name_path_save  =  file_save ;
        QDir dir(name_path_save);
        if (!dir.exists()){
          dir.mkdir(".");
        }
    }    
    return ;
}

bool Nofication_close::isMainThread()
{
    return QThread::currentThread() == qApp->thread();
}
void Nofication_close::on_pushButton_2_clicked() //oke
{   this->Create_Folder();
        Set_Mode() ;
    int ret =  Procss->exec()    ;
    this->close();  
  if(ret == QDialog::Accepted){
      Procss->close() ;
  }
  this->accept() ;
}
void Nofication_close::on_pushButton_clicked()
{
   reject() ;
}
void Nofication_close::on_pushButton_3_clicked()
{
   reject() ;
}
void Nofication_close::Do_Work()
{
    moveToThread(qApp->thread());
    return ;
}
