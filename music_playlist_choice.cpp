#include "music_playlist_choice.h"
#include "ui_music_playlist_choice.h"
#include<QVariant>
#include<QObject>
#include<QQuickItem>
#include<QQmlProperty>
#include<QQmlApplicationEngine>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QQmlContext>
#include<database_process.h>
#include<QMessageBox>
Music_Playlist_choice::Music_Playlist_choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Music_Playlist_choice)
{
    ui->setupUi(this);
    QPixmap PixiBack_Frame("E:/dowload/color-background.png");
    PixiBack_Frame.scaled(this->size() ,Qt::IgnoreAspectRatio ) ;
    QPixmap PixiBack("E:/dowload/color-background.png");
    PixiBack_Frame.scaled(this->size() ,Qt::IgnoreAspectRatio ) ;
    QPalette palette;
       palette.setBrush(QPalette::Background, PixiBack_Frame);
       this->setPalette(palette);
       Set_quick_widget() ;
       this->Thread1 =  async(launch::async , [=](){
           open_database() ;
       }) ;
       ui->progressBar->hide() ;
}

Music_Playlist_choice::Music_Playlist_choice(QWidget *parent, QVector<Infomation *> Present_list, Infomation*Present_Music) :
    QDialog(parent),present_list(Present_list) , present_music(Present_Music),
    ui(new Ui::Music_Playlist_choice)
{
    ui->setupUi(this);
    QPixmap PixiBack_Frame("E:/dowload/color-background.png");
    PixiBack_Frame.scaled(this->size() ,Qt::IgnoreAspectRatio ) ;
    QPixmap PixiBack("E:/dowload/color-background.png");
    PixiBack_Frame.scaled(this->size() ,Qt::IgnoreAspectRatio ) ;
    QPalette palette;
       palette.setBrush(QPalette::Background, PixiBack_Frame);
       this->setPalette(palette);
       Set_quick_widget() ;
       if(this->present_list.size() == 0) {
            this->all_music = false ;
            ui->pushButton_2->setDisabled(true)   ;
       }
       this->Thread1 =  async(launch::async , [=](){
           open_database() ;
       }) ;

}

void Music_Playlist_choice::open_database()
{
  database =  new Database_process(0) ;
  if(database->check_database_open()) {
      list_of_table =  database->list_table() ;
  }
}

void Music_Playlist_choice::close_database()
{
    this->database->Close_datbase() ;
}

void Music_Playlist_choice::signal_name_of_table(QVariant table_name)
{
    name_table = table_name.toString() ;
       ui->progressBar->show() ;
     //  database->Open_database(0) ;

     if(this->all_music == true) {
        QSqlQuery Query ;
        int i = 0 ;
           this->Size = present_list.size()  ;
           for(auto x : this->present_list) {
               i++ ;
               on_progressBar_valueChanged(i) ;
               database->set_database_name(name_table) ;
               database->Add_data_into_database(x) ;
               database->Close_datbase() ;
        }
     }
     else {
         //// BUG here
        database->Close_datbase() ;
        database->set_database_name(name_table) ;
        database->Add_data_into_database(this->present_music)   ;
        on_progressBar_valueChanged(1) ;
        database->Close_datbase()  ;

     }
     ui->progressBar->hide() ;
     ui->progressBar->setValue(0) ;
    database->Close_datbase() ;

     accept() ;
     return ;
}

Music_Playlist_choice::~Music_Playlist_choice()
{
    delete ui;
}

QString Music_Playlist_choice::get_table_name()
{
    return this->name_table ;
}

void Music_Playlist_choice::Set_quick_widget()
{
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop) ;
    ui->quickWidget->setAttribute(Qt::WA_TranslucentBackground) ;
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setSource(QUrl("qrc:/Menu_playlist.qml") );
    ui->quickWidget->show() ;
    ui->quickWidget->rootContext()->setContextProperty("w",this);
    auto obj =  ui->quickWidget->rootObject() ;
    connect(this , SIGNAL(Add_Table_list(QVariant)) , obj , SLOT(load_table(QVariant))) ;
    connect(this , SIGNAL(_Clear_list_signal(QVariant)) , obj , SLOT(slot_clear_list(QVariant))) ;

}

void Music_Playlist_choice::on_pushButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(1) ;
   Thread1.get() ;
   for(auto x : list_of_table) {
        emit(Add_Table_list(x)) ;
   }
   if(this->present_list.size() == 0) {

   }
   this->Size = 1 ;
   this->all_music =  false ;
   return ;
}

void Music_Playlist_choice::on_pushButton_2_clicked()
{
    Thread1.get();    
    ui->stackedWidget->setCurrentIndex(1) ;
    for(auto x : list_of_table) {
         emit(Add_Table_list(x)) ;
    }  
    this->Size  =  this->present_list.size() ;
    this->all_music =  true  ;
    return ;
}

void Music_Playlist_choice::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0) ;
    emit(_Clear_list_signal(true)) ;
}


void Music_Playlist_choice::on_progressBar_valueChanged(int value)
{
    ui->progressBar->setValue((value/this->Size)*100) ;
    if(value == this->Size){
        return ;
    }
}
