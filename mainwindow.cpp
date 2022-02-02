#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include<QDebug>
#include<future>
#include<QVector>
#include"proccesing_file_mp3.h"
#include<QString>
#include<QAbstractButton>
#include<QAbstractItemView>
#include<QMediaPlayer>
#include<QQuickItem>
#include<QVariant>
#include<QQmlProperty>
#include<QMediaMetaData>
#include<QQmlApplicationEngine>
#include<QQmlContext>
#include<QQmlPropertyMap>
#include<QMediaMetaData>
#include"sort_custom.h"
#include<QtWidgets>
#include"nofication_close.h"
#include<QThread>
#include"file_process.h"
#include<music_playlist_choice.h>
#include<create_name_of_table.h>
#include<create_playlist.h>
using namespace  std ;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    QWidget::setWindowTitle("Music Player") ;
    this->Combobox_choice = "Song" ;
    database =  new Database_process(0) ;
    Thread_Process_file =  async(launch::async , [this](){
        control_Process =  new File_Process("E:/Music") ;
        control_Process->Open_directory() ;
    }) ;
    Image_Qquick();
    List_quick() ;
    Name_Music();
    Set_signal_Pause_Or_Play();
    PlayList_page_Set();
    OnPlayingWidget_Playlist() ;
    Music_player =  new QMediaPlayer(this)  ;
    emit Set_name_Music("") ;
    this->Set_connect_Position_datatachange() ;
    this->Set_Stack_Widget() ;
    this->Set_page() ;
   UI_Libary_setting();
   ui->Save->hide() ;
   ui->Add->hide() ;
}
MainWindow::~MainWindow()
{
    delete ui;
}
/// Home
void MainWindow::View(){
   emit clear_list_music(true) ;
   for(auto x : LIS_MP3) {
       emit Set_List_Path_name(x ,MP3_Process->get_name(x) , MP3_Process->get_Author(x) ,  MP3_Process->get_Qualification(x)) ;
       emit Get_signal_infomation(x);
   }
   this->get_size(LIS_MP3.size()) ;
}

void MainWindow::Set_Stack_Widget()
{
    this->Stack_Next.push(1) ;
    this->Stack_Next.push(0) ;
}

void MainWindow::Set_Stack_Widget_Main()
{
 return ;
}
void MainWindow::Set_connect_Position_datatachange()
{
    connect(Music_player , &QMediaPlayer::positionChanged , this , &MainWindow::On_Position_change) ;
    connect(Music_player , &QMediaPlayer::durationChanged , this ,  &MainWindow::On_Duration_change) ;
    connect(ui->horizontalSlider, &QAbstractSlider::valueChanged , this , &MainWindow::Set_Pos) ;
    connect(Music_player , &QMediaPlayer::positionChanged , this , &MainWindow::check_Finished) ;
}
void MainWindow::Image_Qquick(){
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setSource(QUrl("qrc:/Disk_Rotate.qml") );
    ui->quickWidget->show();
    auto  obj =  ui->quickWidget->rootObject()  ;
    connect(this , SIGNAL(set_Duration(QVariant)) , obj , SLOT(set_duration(QVariant)));
    connect(this ,  SIGNAL(Set_pause(QVariant)) , obj , SLOT(set_pause(QVariant)));
    emit set_Duration(false);
    emit Set_pause(false);
}
void MainWindow::List_quick()
{
    ui->quickWidget_2->setAttribute(Qt::WA_AlwaysStackOnTop) ;
    ui->quickWidget_2->setAttribute(Qt::WA_TranslucentBackground) ;
    ui->quickWidget_2->setClearColor(Qt::transparent);
    ui->quickWidget_2->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget_2->setSource(QUrl("qrc:/List_Qquickwidget.qml") );
    ui->quickWidget_2->show() ;
    auto obj =  ui->quickWidget_2->rootObject() ;
    ui->quickWidget_2->rootContext()->setContextProperty("w",this);
    //ui->quickWidget_2;
    connect(this ,  SIGNAL(Get_size(QVariant)) , obj , SLOT(get_size(QVariant))) ;
    connect(this ,  SIGNAL(Combox_signal(QVariant)) , obj , SLOT(restart_Fitler_list(QVariant))) ;
    connect(this ,  SIGNAL(Fitler_LST(QVariant , QVariant , QVariant , QVariant,QVariant,QVariant)) , obj , SLOT(filter_List(QVariant , QVariant , QVariant , QVariant , QVariant,QVariant))) ;
    connect(this ,  SIGNAL(Set_List_Path_name(QVariant , QVariant , QVariant , QVariant)) , obj , SLOT(set_list_path_name(QVariant , QVariant , QVariant , QVariant)));
    connect(this ,  SIGNAL(Search_field(QVariant , QVariant , QVariant , QVariant)) , obj , SLOT(get_result(QVariant , QVariant , QVariant , QVariant)));
    connect(this ,  SIGNAL(clear_list_music(QVariant)) , obj , SLOT(clear_list_music(QVariant)));

}
void MainWindow::Set_label_Name(QString name){
    Get_data_change(Music_player);
    this->Thread_for =  async(launch::async , [=]() {
       for(auto x : Infoma ) {
            if(x->get_Full_name() == name) {
                Present_Music = x ;
            }
       }
    }) ;
    ui->Music_name_label_2->setText(name) ;
    emit Set_name_Music(name) ;
}
void MainWindow::Name_Music()
{
    auto obj2 = ui->quickWidget_2->rootObject()  ;
    connect(this ,  SIGNAL(Set_name_Music(QVariant)) , obj2 , SLOT(get_name_of_music(QVariant)));    
}
void MainWindow::Set_signal_Pause_Or_Play()
{
    auto obj2 = ui->quickWidget_2->rootObject()  ;
    connect(this ,  SIGNAL(get_signal_Pause_or_Play(QVariant)) , obj2 , SLOT(get_sgnal_play_or_pause(QVariant))) ;
    emit get_signal_Pause_or_Play(count_play);
}

void MainWindow::Set_infor(QString name)
{
    //QMediaPlayer* Infomusic = new QMediaPlayer(this) ;
    Infomusic->setMedia(QUrl::fromLocalFile(MP3_Process->get_path_by_name(name)));
}
void MainWindow::connect_qml(const QString &name_of_music)
{
    Music_player->stop() ;
    this->TOP =  name_of_music ;
    this->Play()     ;
}

int MainWindow::get_size(const int size)
{
    emit Get_size(size) ;
    return size ;
}

void MainWindow::Fitler(QString re_quire){
    QStringList temp ;    
    if(re_quire.size() < 6) {
        Result*item = new Result(Infoma) ;
        Prsent_list(item->Quality_Fitler(re_quire), re_quire) ;
        MP3_Process->Set_name_music_tail(item->get_path_name()) ;
    }
    else {
        Prsent_list(Infoma,re_quire) ;
    }
}
void MainWindow::Prsent_list(QVector<Infomation *> arg1 ,QString signal) {
    Present_list =  arg1 ;
    for(auto x : arg1){
        emit Fitler_LST(x->get_Full_name() ,  x->get_Name() , x->get_Artist() ,x->get_qualification() , arg1.size(),signal ) ;
    }
   this->get_size(arg1.size()) ;
}
void MainWindow::Set_page()
{
    QPixmap PixiBack_Frame(":/Image/color-background.png");
    //1610534159_450_Tong-hop-100-Background-dep-nhat.jpg
    PixiBack_Frame.scaled(this->size() ,Qt::IgnoreAspectRatio ) ;
    QPixmap PixiBack(":/Image/color-background.png");
    PixiBack_Frame.scaled(this->size() ,Qt::IgnoreAspectRatio ) ;
    QPalette palette;
       palette.setBrush(QPalette::Background, PixiBack_Frame);
       this->setPalette(palette);
       QPixmap Pixi(":/Image/USer.png") ;
       ui->Image1->setPixmap(Pixi.scaled(70,70)) ;
       QPixmap pixi_login(":/Image/file.png") ;
       QIcon ButtonIcon(pixi_login);
       ui->Browser->setIcon(ButtonIcon);
       ui->Browser->setIconSize(QSize(100  ,50));
       QPixmap pixi_Home(":/Image/Home.png") ;
       QIcon ButtonIcon1(pixi_Home);
       ui->Home->setIcon(ButtonIcon1);
       ui->Home->setIconSize(QSize(120  ,30));
       QPixmap pixi_Playlist(":/Image/Favorite.png") ;
       QIcon ButtonIcon2(pixi_Playlist);
       ui->Favorite->setIcon(ButtonIcon2);
       ui->Favorite->setIconSize(QSize(100  ,30));
       QPixmap PixiStart(":/Image/Play.png");
       ui->Play_or_Pause->setIcon(PixiStart) ;
        ui->Play_or_Pause->setIconSize(QSize(40,40)) ;
        ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection) ;
        ui->Time->setText("00:00");
       // string volumn = to_string(ui->Volumn->value())+'%' ;
       // ui->value_volumn->setText( QString::fromStdString(volumn));
        QPixmap pixi_Volumn (":/Image/Unmute.png") ;
        QIcon icon(pixi_Volumn) ;
        ui->Volum_button->setIcon(icon) ;
        ui->Volum_button->setIconSize(QSize(20 ,20));
        QPixmap Pixi_next("E:/dowload/next.png");
        ui->Next->setIcon(Pixi_next) ;
        ui->Next->setIconSize(QSize(40,40)) ;
        QPixmap Pixi_Pre("E:/dowload/Prev.png");
        ui->Prev->setIcon(Pixi_Pre) ;
        ui->Prev->setIconSize(QSize(40,40)) ;
        QPixmap Pixi_Random("E:/dowload/Random_OF.png")    ;
        QIcon icon_Random(Pixi_Random) ;
        ui->Random->setIcon(icon_Random) ;
        ui->Random->setIconSize((QSize(30,30))) ;
        QPixmap Pixi_Loop("E:/dowload/step_by_step.png")    ;
        QIcon icon_loop(Pixi_Loop) ;
        ui->loop->setIcon(icon_loop) ;
        ui->loop->setIconSize((QSize(30,30))) ;
        QPixmap Pixi_LIb("E:/dowload/Lib.png")    ;
        QIcon icon_Lib(Pixi_LIb) ;
        ui->Libary->setIcon(icon_Lib) ;
        ui->Libary->setIconSize((QSize(90,50))) ;
        QPixmap Pixi_Arrow_next("E:/dowload/Arrow_next.png")    ;
        QIcon icon_Arrow_next(Pixi_Arrow_next) ;
        ui->Arrow_next->setIcon(icon_Arrow_next) ;
        ui->Arrow_next->setIconSize((QSize(20,140))) ;
        QPixmap Pixi_Arrow_Prev("E:/dowload/Arrow_Prev.png")    ;
        QIcon icon_Arrow_Prev(Pixi_Arrow_Prev) ;
        ui->arrow_Prev->setIcon(icon_Arrow_Prev) ;
        ui->arrow_Prev->setIconSize((QSize(20,140))) ;
        QPixmap List("E:/QT5/Music_Player/Image/List.png") ;
        ui->List->setPixmap(List.scaled(40,40)) ;
        QPixmap Add("E:/QT5/Music_Player/Image/Add.png")    ;
        QIcon Add_(Add) ;
        ui->Add->setIcon(Add) ;
        ui->Add->setIconSize(QSize(30,30));

        if(count_check == false) {
            QPixmap pixi_Volumn ("E:/dowload/Unmute.png") ;
            QIcon icon(pixi_Volumn) ;
            ui->Volum_button->setIconSize(QSize(20  ,20));
            count_check = true ;
        }
        else {
             QPixmap pixi_Volumn ("E:/dowload/Mute.png") ;
             QIcon icon(pixi_Volumn) ;
             ui->Volum_button->setIconSize(QSize(20  ,20));
            count_check = false ;
        }        
}
void MainWindow::Set_Time_0(quint64 time)
{
    if(time == 0 ) {
          ui->Time_active->setText("00:00");
    }
    else {
       QString time_ = Format_Time(time);
        ui->Time_active->setText(time_);
    }
}
QString MainWindow::Format_Time(quint64 Time)
{
    qint64 seconds = Time / 1000;
    qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    return QStringLiteral("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
}
void MainWindow::on_Browser_clicked()
{
  future<void> MUSIC_NAME_CHECK ;
  vector<QString> MUSIC ;
  QStringList fileName =   QFileDialog::getOpenFileNames(this,
        tr("choose"), tr("") ) ;
       if (fileName.isEmpty()) {
          return;
         }

      MP3_Process =  new Proccesing_File_MP3(fileName) ;
      Browser_Process() ;

    return  ;
}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item){
      QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
      ui->Music_name_label_2->setText(list.at(0)->text())   ;
      count_play  =  true;
      emit get_signal_Pause_or_Play(count_play);
      this->TOP = list.at(0)->text() ;
      this->Play();
}
void MainWindow::On_Duration_change(quint64 Duration){
    duration =  Duration ;
    ui->horizontalSlider->setRange(0,Duration);
    Set_Time_0(duration) ;
}
void MainWindow::On_Position_change(quint64 Position){
    ui->horizontalSlider->setValue(Position) ;
    ui->Time->setText(Format_Time(Position)) ;
    Pos = Position ;
}
void MainWindow::on_Play_or_Pause_clicked()
{
    if(LIS_MP3.empty()){
        int ret = QMessageBox::warning(this, tr("Warning"),
                                         tr("This List is empty"),
                                         QMessageBox::Ok);
        return  ;
    }
    else {        
        emit get_signal_Pause_or_Play(!count_play);
    if(this->count_play == false) {

        count_play =  true ;
        QPixmap PixiStart("E:/dowload/Pause.png");
        ui->Play_or_Pause->setIcon(PixiStart) ;
        ui->Play_or_Pause->setIconSize(QSize(40,40)) ;
        Music_player->play();
        emit Set_pause(false);
        emit set_Duration(true);
    }
    else {
        count_play =  false ;
        QPixmap PixiStart("E:/dowload/Play.png");
        ui->Play_or_Pause->setIcon(PixiStart) ;
        ui->Play_or_Pause->setIconSize(QSize(40,40)) ;
        Music_player->pause() ;
        emit Set_pause(true);
    }
    }
}
void MainWindow::on_Volumn_valueChanged(int value)
{
    ui->horizontalSlider->setTickPosition(ui->horizontalSlider->tickPosition()) ;
    Music_player->setVolume(value) ;
}
void MainWindow::on_Volum_button_clicked(bool checked)
{
    if(count_check == false) {
        QPixmap pixi_Volumn ("E:/dowload/Unmute.png") ;
        QIcon icon(pixi_Volumn) ;
        ui->Volum_button->setIcon(icon) ;
        ui->Volum_button->setIconSize(QSize(20 ,20));
        ui->Volumn->setValue(50) ;
        count_check = true ;
    }
    else {
         QPixmap pixi_Volumn ("E:/dowload/Mute.png") ;
         QIcon icon(pixi_Volumn) ;
         ui->Volum_button->setIcon(icon) ;
         ui->Volum_button->setIconSize(QSize(20 ,20));
         ui->Volumn->setValue(0) ;
        count_check = false ;
    }
}
void MainWindow::on_Random_clicked()
{
    if(Random_check == false ) {
        Random_check = true ;
        QPixmap Pixi_Random("E:/dowload/Random_On.png")    ;
        QIcon icon(Pixi_Random) ;
        ui->Random->setIcon(icon) ;
        ui->Random->setIconSize((QSize(30,30))) ;
        if(!LIS_MP3.empty()){
            MP3_Process->Connect_change(Random_check) ;
            this->TOP = MP3_Process->Get_TOP();
        }
    }
    else  {
        Random_check = false ;
        QPixmap Pixi_Random("E:/dowload/Random_OF.png")  ;
        QIcon icon(Pixi_Random) ;
        ui->Random->setIcon(icon) ;
        ui->Random->setIconSize((QSize(30,30))) ;
         if(!LIS_MP3.empty()){
             MP3_Process->Connect_change(Random_check) ;
             this->TOP = MP3_Process->Get_TOP();
         }
    }
}
void MainWindow::Set_Pos(int Pos){
    if(qAbs(Music_player->position() - Pos) > 99 ) {
        Music_player->setPosition(Pos) ;
    }
    return ;
}
void MainWindow::on_loop_clicked()
{
    if(Loop_check == false ) {
        QPixmap Pixi_Loop("E:/dowload/loop.png")  ;
            QIcon icon(Pixi_Loop) ;
            ui->loop->setIcon(icon) ;
            ui->loop->setIconSize((QSize(30,30))) ;
            Loop_check =  true ;
        }
        else  {
        QPixmap Pixi_Loop("E:/dowload/step_by_step.png")    ;
            QIcon icon(Pixi_Loop) ;
            ui->loop->setIcon(icon) ;
            ui->loop->setIconSize((QSize(30,30))) ;
            Loop_check = false ;
        }
}
void MainWindow::on_arrow_Prev_clicked(){
    if(Stack_Prev.empty()){
    }
    else {
        Stack_Next.push(Stack_Prev.top()) ;
        Stack_Prev.pop() ;
        ui->stackedWidget_2->setCurrentIndex(Stack_Next.top()) ;
    }
}
void MainWindow::on_Arrow_next_clicked(){
    if(Stack_Next.empty()) {

    }
    else {
        Stack_Prev.push(Stack_Next.top()) ;
        Stack_Next.pop() ;
        if(!Stack_Next.empty()){
        ui->stackedWidget_2->setCurrentIndex(Stack_Next.top()) ;
          }
    }
}
void MainWindow::on_Next_clicked(){
    this->MP3_Process->Next() ;
    TOP = this->MP3_Process->Get_TOP() ;
    count_play  =  true;
    Play();
}
void MainWindow::on_Prev_clicked()
{
     if(ui->horizontalSlider->value() > 10) {
        Music_player->stop() ;
        Play() ;
     }
     else {
        this->MP3_Process->Prev() ;
        this->TOP = this->MP3_Process->Get_TOP() ;
        count_play  =  true;
        Play();
     }
}
void MainWindow::Play()
{
    QPixmap PixiStart("E:/dowload/Pause.png");
    ui->Play_or_Pause->setIcon(PixiStart) ;
    ui->Play_or_Pause->setIconSize(QSize(40,40)) ;
    if(MP3_Process->get_path_by_name(this->TOP) == "") {
         QMessageBox::critical(this, tr("My Application"),
                                         tr("Path is not existed "),
                                         QMessageBox::Cancel);
        MP3_Process->Next() ;
    }
    else {
        Music_player->setMedia(QUrl::fromLocalFile(MP3_Process->get_path_by_name(this->TOP))) ;
        Set_label_Name(this->TOP) ;
        emit this->set_Duration(true) ;
        Music_player->play() ;
    }
    return ;
}
void MainWindow::check_Finished(qint64 Pos){
    if(Loop_check == false) {
    if(ui->Time->text() != "00:00"){
        if(duration == Pos){
            this->MP3_Process->Next() ;
            TOP =  this->MP3_Process->Get_TOP();
            count_play  =  true;
            Play();
        }
    }
    }
    else {
       if(Pos == duration){
            Music_player->stop() ;
           Music_player->play();
       }
    }
    return ;
}
void MainWindow::Metadatachanged(){
    if(Music_player->isMetaDataAvailable()){
    }
}
void MainWindow::OnMedia_changed(QMediaPlayer::MediaStatus status,QMediaPlayer *media)
{
    if(status ==  QMediaPlayer::LoadedMedia){
      Get_data_change(media);
    }
}
void MainWindow::Get_data_change(QMediaPlayer *player){
    QStringList metadtalist =   player->availableMetaData();
    QString metadata_key;
    QVariant var_data;
    QString name ;
    QString date  ;
    name = player->metaData(QMediaMetaData::Title).toString() ;
}
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    emit Combox_signal(arg1) ;
    Fitler(arg1) ;
}

void MainWindow::Set_Infomation_of_Music()
{
    if(Infoma.empty()){
        Infoma.resize(LIS_MP3.size()) ;
        for(int i = 0; i < Infoma.size() ; i++ ) {
            QString x  = LIS_MP3[i] ;
            QString full_path = MP3_Process->get_path_by_name(x) ;
            Infomation*info = new Infomation(x ,MP3_Process->get_name(x) , MP3_Process->get_Author(x) ,  MP3_Process->get_Qualification(x) ,full_path ) ;
            List_Path.insert(MP3_Process->get_path(full_path)) ;
            Infoma[i] = info  ;
        }
    }
}
void MainWindow::text_Search_change(const QString &text, int i)
{
    Result*temp ;
    if(i == 0 ) {
        temp =  Filter_Search ;
    }
    else if(i == 1) {
        temp = Filter_Search_playlist ;
    }
    else if( i== 2) {
        temp = Filter_Search_Table_playlist ;

        this->Combobox_choice = "Song" ;
    }

   if(text != "") {
       if(this->Combobox_choice == "Song") {
       if(text.size() < Stack_step.size()) {
           Stack_step.pop() ;
           this->Search_Result =  temp->Name_search_Filter(text[text.size()-1],Stack_step.size()) ;
       }
       else if(text.size() > Stack_step.size()) {
           Stack_step.push_back(text[text.size()-1]) ;
          this->Search_Result =temp->Name_search_Filter(text[text.size()-1],Stack_step.size()) ;
       }
       }
       else {
           if(text.size() < Stack_step.size()) {
               Stack_step.pop() ;
               temp->Artisit_search_Filter(text[text.size()-1],Stack_step.size()) ;
           }
           else if(text.size() > Stack_step.size()) {
               Stack_step.push_back(text[text.size()-1]) ;
              this->Search_Result =temp->Artisit_search_Filter(text[text.size()-1],Stack_step.size()) ;
           }
       }
   }
   else {
       if(this->Combobox_choice == "Song") {
       if(!Stack_step.empty()){
           Stack_step.pop() ;
           this->Search_Result =temp->Name_search_Filter(text[text.size()-1],Stack_step.size()) ;
       }
       }
       else {
           if(!Stack_step.empty()){
               Stack_step.pop() ;
               this->Search_Result =temp->Artisit_search_Filter(text[text.size()-1],Stack_step.size()) ;
           }
       }

   }
   for(auto x : this->Search_Result) {
       if(i == 0 ) {
             emit Search_field(x->get_Full_name() ,  x->get_Name() , x->get_Artist() ,x->get_qualification() ) ;
       }
       else if(i == 2) {
            emit Search_field_table(x->get_Full_name())            ;
       }
       else if( i == 1) {
            emit Search_field_playlist(x->get_Full_name() ,  x->get_Name() , x->get_Artist() ,x->get_qualification());
       }

   }
   this->get_size(this->Search_Result.size()) ;
   return  ;
}
QString MainWindow::combobox_Text(const QString &text)
{
         if(text != this->Combobox_choice){
             this->combobox_change =  true ;
             this->Combobox_choice =  text ;
         }
         else {
             this->combobox_change =  false  ;
        }
         return text ;
}
void MainWindow::closeEvent(QCloseEvent *event){
   if(Infoma.empty() == false){
       Nofication_close*nofiaction =  new Nofication_close(this ,this->Infoma,this->List_Path) ;
      int ret =  nofiaction->exec() ;
       if(ret == QDialog::Accepted){
           event->ignore() ;
       }
       else {
           event->accept() ;
       }
   }
   return ;
}
///                         Playlist Page
void MainWindow::on_Favorite_clicked()
{
    database->Close_datbase() ;
    ui->stackedWidget->setCurrentIndex(1) ;
    emit clear_list_model(true) ;

    if(database->check_database_open() == false) {
    if(data_file.empty()) {
        Thread_Process_file.get() ;
        data_file =  control_Process->get_label() ;
        this->check_file_change = true  ;
    }
    if(check_file_change == true){
        for(auto x : control_Process->get_label()) {
            emit Get_list_file(x);
        }
        check_file_change =  false ;
        }
    }
    else{
//        database->Close_datbase() ;
        QStringList table = database->list_table() ;
        shared_future <void> Table_Thread= async(launch::async , [=](){
            this->Table_list.clear() ;
            for(auto x : table) {
                Infomation*info =  new Infomation(x,x,"","","") ;
                Table_list.push_back(info)  ;
           }


        }) ;
         for(auto x :table) {
             emit Get_list_file(x);

        }
         Table_Thread.get() ;
         database->Close_datbase() ;
         Filter_Search_Table_playlist =  new Result(Table_list) ;
    }
    return ;
}
void MainWindow::PlayList_page_Set()
{
    ui->quickWidget_Playlist->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_Playlist->setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget_Playlist->setClearColor(Qt::transparent);
    ui->quickWidget_Playlist->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget_Playlist->setSource(QUrl("qrc:/Playlist.qml"));
    ui->quickWidget_Playlist->show();
    auto obj2 =  ui->quickWidget_Playlist ->rootObject() ;
    ui->quickWidget_Playlist->rootContext()->setContextProperty("w",this);
    connect(this ,  SIGNAL(Get_list_file(QVariant)) , obj2 , SLOT(get_List_of_File_Name(QVariant))) ;
    connect(this , SIGNAL(clear_list_model(QVariant)) , obj2 ,SLOT(clear_Grid_view(QVariant))) ;
    connect(this , SIGNAL(clear_list_view(QVariant)) , obj2 ,  SLOT(clear_list_view(QVariant))) ;
    connect(this , SIGNAL(add_data_to_QML(QVariant , QVariant , QVariant , QVariant)) , obj2 ,  SLOT(set_list_path_name(QVariant , QVariant , QVariant , QVariant))) ;
    connect(this ,  SIGNAL(Search_field_table(QVariant )) , obj2 , SLOT(filter_Playlist_table(QVariant)));
    connect(this ,  SIGNAL(Search_field_playlist(QVariant , QVariant , QVariant , QVariant )) , obj2 , SLOT(filter_Playlist_music(QVariant , QVariant , QVariant , QVariant )));


}
void MainWindow::OnPlayingWidget_Playlist()
{
    ui->quickWidget_onPlaying->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_onPlaying->setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget_onPlaying->setClearColor(Qt::transparent);
    ui->quickWidget_onPlaying->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget_onPlaying->setSource(QUrl("qrc:/OnPlaying.qml"));
    ui->quickWidget_onPlaying->show();    
}

void MainWindow::on_Home_clicked()
{
    ui->stackedWidget->setCurrentIndex(0) ;
    database->Close_datbase() ;
}
void MainWindow::_Get_element_in_file(QString file_name)
{
    emit clear_list_view(true) ;
    ui->Playlist_2->setText(file_name);
    this->database->Open_database(0) ;
    this->database->set_database_name(file_name) ;
    this->database->Load_data_from_database() ;
    QVector<Infomation*> temp_list = this->database->get_Table_of_data() ;
    database->Close_datbase() ;
    database->Close_datbase() ;
    Path_name.clear() ;
        this->Set_Infomation_of_Music() ;
        this->Filter_Search_playlist =  new Result(temp_list) ;
        this->temp_Infoma = temp_list ;

    Thread_Path = async(launch::async , [=](){
        for(auto x : temp_list) {
            Path_name.push_back(x->get_Path_name()) ;
        }
    }) ;
    for(auto x : temp_list) {
        emit add_data_to_QML(x->get_Full_name(),x->get_Name() ,x->get_Artist(),x->get_qualification()  ) ; // //x->get_Full_name()
    }
}

void MainWindow::signal_add_new_playlist(bool bool_signal)
{
   Create_playlist*create =  new Create_playlist() ;   
   int ret = create->exec() ;
   if(ret == QDialog::Accepted) {
       database->Create_table_name(create->get_name_table()) ;
       on_Favorite_clicked() ;
   }
   database->Close_datbase() ;
}

void MainWindow::check_and_get_List(QVariant x)
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to play '" +this->database->get_name_of_Present_table() +"' playlist ?");
    msgBox.setStandardButtons(QMessageBox::Ok |  QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    QVector<Infomation*> temp  = Infoma ;
    int ret = msgBox.exec();
    if(ret == msgBox.Ok) {
        Thread_Path.get() ;
        Infoma = this->temp_Infoma ;
        MP3_Process =  new Proccesing_File_MP3(this->Path_name) ;
        Browser_Process() ;
        ui->Playlist->setText(this->database->get_name_of_Present_table()) ;
        Infoma = temp ;
    }
}

void MainWindow::rename_table(QVariant x)
{
    QString str = x.toString() ;
    Create_name_of_table*rename =  new Create_name_of_table(this,str) ;
    int ret =  rename->exec() ;
    if(ret == QDialog::Accepted) {
        on_Favorite_clicked() ;
    }
}

void MainWindow::delete_table(QVariant x)
{

    int _ret = QMessageBox::warning(this, tr("Warning"),
                                     tr("Do you want to delete this table"),
                                     QMessageBox::Ok | QMessageBox::Cancel);
    if(_ret == QMessageBox::Ok) {
        this->database->delete_table(x.toString()) ;
        on_Favorite_clicked() ;
    }
    this->database->Close_datbase() ;
    return  ;
}

void MainWindow::delete_music_playlist(QVariant x)
{
     QString name  =  x.toString() ;
     this->database->Open_database(0) ;
     this->database->delete_music(name) ;
     this->database->Close_datbase() ;
     return ;
}

void MainWindow::add_Music_in_playlist()
{
    QVector<Infomation*> temp   ;
    QVector<QString>     LST  ;
    QStringList fileName =   QFileDialog::getOpenFileNames(this,
          tr("choose"), tr("") ) ;
         if (fileName.isEmpty()) {
            return;
           }
       Proccesing_File_MP3*MP3 = new Proccesing_File_MP3(fileName)     ;
       MP3->check_File() ;
       LST = MP3->get_MP3() ;
       temp.resize(LST.size()) ;
       for(int i = 0; i < temp.size() ; i++ ) {
           QString x  = LST[i] ;
           QString full_path = MP3->get_path_by_name(x) ;
           Infomation*info = new Infomation(x ,MP3->get_name(x) , MP3->get_Author(x) ,  MP3->get_Qualification(x) ,full_path ) ;
           emit add_data_to_QML(info->get_Full_name(),info->get_Name() ,info->get_Artist(),info->get_qualification()  ) ; // //x->get_Full_name()
           this->database->Add_data_into_database(info) ;
      }
       return ;
}

void MainWindow::delete_in_main_list(QVariant x)
{
    shared_future<void> delete_music ;
    delete_music = async(launch::async , [=] () {
        int i = 0  ;
        for(auto item : Infoma) {
            if(item->get_Name() == x.toString()) {
                Infoma.remove(i);
                break ;
            }
            i++ ;
        }
    }) ;
    if(ui->Playlist->text() != "") {
        delete_music_playlist(x) ;
        delete_music.get() ;
    }
    else {
        delete_music.get() ;
    }
}

void MainWindow::add_Music_into_playlist(QVariant x)
{
    QString str = x.toString() ;
    Infomation*_Info = new Infomation("","","","","") ;
    QVector<Infomation*> temp ;

    for(auto x : Infoma) {
        if(x->get_Name() == str) {
            _Info->Copy(*x) ;
            break ;
        }

    }

    Music_Playlist_choice*Add =  new Music_Playlist_choice(this , temp , _Info) ;
    int ret = Add->exec() ;
    if(ret == QDialog::Accepted) {
    }
}

void MainWindow::reset_datbase(QVariant x)
{
    database->Close_datbase() ;
    ui->Playlist_2->setText("") ;
}

void MainWindow::load_Music_all_from_libary(QVariant x)
{
    Infoma = temp_Infoma ;
    MP3_Process =  new Proccesing_File_MP3(this->temp_Path) ;
    Browser_Process() ;
    temp_Infoma.clear() ;
}

void MainWindow::play_music(QVariant full_name , QVariant name , QVariant artist  , QVariant Qualfication, QVariant Path)
{
    Infomation* info = new Infomation(full_name.toString() , name.toString() , artist.toString() ,  Qualfication.toString() ,  Path.toString() ) ;
    if(Infoma.size() ==  0) {
        this->Infoma.push_back(info) ;
        this->Path_name.push_back(Path.toString()) ;
    }
    else {
       for(auto x : Infoma) {
           if(x->get_Full_name() == full_name.toString()) {
              break ;
           }
           else {
               Infoma.push_back(x) ;
               this->Path_name.push_back(Path.toString()) ;
               break ;
           }
       }
    }
    MP3_Process =  new Proccesing_File_MP3(Path_name) ;
    Browser_Process() ;
   Play()  ;

}

void MainWindow::add_list()
{
    on_Browser_clicked() ;
}

void MainWindow::save_list()
{
    on_Save_clicked() ;
}

void MainWindow::delete_all()
{
    Infoma.clear() ;
    this->Path_name.clear() ;
    this->TOP = ""     ;
    ui->horizontalSlider->setValue(0) ;
    ui->Music_name_label_2->setText("") ;
    MP3_Process->Reset_all() ;
    Music_player->stop() ;
}

void MainWindow::save_music_in_playlist()
{
    on_Add_clicked() ;
}

void MainWindow::delete_music_in_libary(QVariant x)
{
    Database_process*_database = new Database_process(1) ;
    QString name  =  x.toString() ;
    _database->Open_database(1) ;
    _database->set_database_name("list1") ;
    _database->delete_music(name) ;
    _database->Close_datbase() ;
    this->libary_change =  true  ;
    return ;
}

void MainWindow::delete_all_music_in_libary(QVariant x)
{
    Database_process*_database = new Database_process(1) ;
    QString name  =  x.toString() ;
    _database->Open_database(1) ;
    _database->set_database_name("list1") ;
    _database->delete_all_music_in_table(name) ;
    _database->Close_datbase() ;
    this->libary_change =  true  ;
    return ;
}

void MainWindow::play_all()
{
    int _ret = QMessageBox::warning(this, tr("Warning"),
                                     tr("Do you want to replace this present list"),
                                     QMessageBox::Ok |  QMessageBox ::No);
    if(_ret ==  QMessageBox::Ok){
        emit clear_list_music(true) ;
        load_Music_all_from_libary(true) ;
        this->TOP = (*Infoma.begin())->get_Full_name() ;
        Play() ;
        Music_player->play() ;
    }
    else {
        QStringList path ;
        for(auto x : temp_Infoma) {
            Infoma.push_back(x) ;
            emit Set_List_Path_name(x->get_Full_name() ,x->get_Name() ,x->get_Artist() , x->get_qualification()) ;
            path.push_back(x->get_Path_name()) ;
        }
        Proccesing_File_MP3 *_tem_ = new Proccesing_File_MP3(path) ;
        _tem_->check_File() ;
        this->TOP = (*Infoma.begin())->get_Full_name() ;
        Play() ;
    }
    return  ;
}
void MainWindow::load_into_libary()
{
    Database_process*data =  new Database_process(1) ;
    data->set_database_name("list1") ;
    QVector<Infomation*> temp   ;
    QVector<QString>     LST  ;
    QStringList fileName =   QFileDialog::getOpenFileNames(this,
          tr("choose"), tr("") ) ;
         if (fileName.isEmpty()) {
            return;
           }
       Proccesing_File_MP3*MP3 = new Proccesing_File_MP3(fileName)     ;
       MP3->check_File() ;
       LST = MP3->get_MP3() ;
       temp.resize(LST.size()) ;
       data->Open_database(1) ;

       for(int i = 0; i < temp.size() ; i++ ) {
           QString x  = LST[i] ;
           QString full_path = MP3->get_path_by_name(x) ;
           Infomation*info = new Infomation(x ,MP3->get_name(x) , MP3->get_Author(x) ,  MP3->get_Qualification(x) ,full_path ) ;
           emit Set_List_Path_name_Libary(info->get_Full_name(),info->get_Name() ,info->get_Artist(),info->get_qualification() ,info->get_Path_name() ) ; // //x->get_Full_name()
           data->Add_data_into_database(info) ;

           this->thread_artist.emplace_back([=](){
               Insert_into_Artist_list(info) ;
           }) ;
      }

      data->Close_datbase() ;
      delete data ;
}

void MainWindow::signal_Artist_page()
{    
    if(Artist.size() == 0) {
        for(auto &x : this->thread_artist ) {
            if(x.joinable()) {
                x.join() ;
            }
        }
    }
        for(auto x : this->Artist) {
            emit ADD_artist(x.first) ;
        }

        return ;
}

void MainWindow::signal_Artist(QVariant name)
{
  temp_Infoma.clear() ;
  emit clear_Artist_music() ;
  QString Name =  name.toString() ;

  ui->label_4->setText("Singer : " + Name ) ;
  this->temp_Infoma = Artist[Name]  ;
  for(auto x : temp_Infoma) {
        emit add_music_artist(x->get_Full_name(),x->get_Name() ,x->get_Artist(),x->get_qualification(),x->get_Path_name()) ;
  }
  return ;

}

void MainWindow::back_signal()
{
    ui->label_4->setText("Libary") ;
    return ;
}

void MainWindow::on_Add_clicked()
{
    if(this->Infoma.size() == 0 || this->Present_Music->get_Path_name() == "")  {
        QMessageBox::warning(this, tr("Warning"),
                                         tr("This List is empty"),
                                         QMessageBox::Ok);
    }
    else {
        Thread_for.get() ;

        Music_Playlist_choice*choice = new Music_Playlist_choice(this,this->Infoma , this->Present_Music ) ;
        int ret  =  choice->exec() ;
        if(ret == QDialog::Accepted) {
        }
    }    
}
void MainWindow::Browser_Process()
{
    Infoma.clear() ;
    check = async(launch::async , [this](){
         MP3_Process->check_File() ;
     }) ;
     check.wait() ;
     check.get() ;
     LIS_MP3 = MP3_Process->get_MP3() ;

     future<void> Thread1 =  async(launch::async , [this](){
         this->Set_Infomation_of_Music() ;
         Filter_Search =  new Result(Infoma) ;
     });
     this->View() ;

     MP3_Process->Set_Random_Or_Essential()  ;
     MP3_Process->Connect_change(Random_check) ;

     this->TOP = MP3_Process->Get_TOP();
     if(MP3_Process->get_path_by_name(this->TOP) == "") {
        QMessageBox::critical(this, tr("My Application"),
                                          tr("Path is not existed "),
                                          QMessageBox::Cancel);
         MP3_Process->Next() ;

     }
     else {
         Music_player->setMedia(QUrl::fromLocalFile(MP3_Process->get_path_by_name(this->TOP))) ;
         Set_label_Name(this->TOP) ;
     }

     Thread1.get() ;
}
/// libary clicked
void MainWindow::on_Save_clicked()
{
    if(Infoma.size() == 0)   {
       QMessageBox::warning(this, tr("Warning"),
                                         tr("This List is empty"),
                                         QMessageBox::Ok);
    }
    else {
    int ret = QMessageBox::warning(this, tr("Warning"),
                                     tr("Do you want to save this list music in"),
                                     QMessageBox::Ok | QMessageBox::Cancel) ;
    if(ret == QMessageBox::Ok) {
        Database_process*database_list =  new Database_process(1) ;
        database_list->Open_database(1) ;
        database_list->set_database_name("list1") ;
        for(auto x : Infoma) {
            database_list->Add_data_into_database(x)   ;
        }
        database_list->Close_datbase() ;
        delete database_list ;
    }
    else {
          return ;
       }
    }
}

void MainWindow::on_Libary_clicked()
{
    ui->stackedWidget->setCurrentIndex(2) ;
    temp_Infoma =  Temp_Info ;
    if(temp_Infoma.size() == 0 || this->libary_change == true) {
        this->temp_Path.clear();
        Database_process*database_list =  new Database_process(1) ;
        database_list->set_database_name("list1") ;
        database_list->Load_data_from_database() ;
        QVector<Infomation*> temp = database_list->get_Table_of_data() ;
        database_list->Close_datbase() ;
        this->temp_Infoma =  temp ;
        emit clear_libary_Music(true) ;

        if(this->Artist.size() == 0 ) {
        future<void> thread_1 =  async(launch::async,[=](){
            for(auto x : temp) {
                this->thread_artist.emplace_back([=](){
                Insert_into_Artist_list(x) ;
            }) ;
            }
        }) ;

        for(auto x : temp ){
            emit Set_List_Path_name_Libary(x->get_Full_name(),x->get_Name() ,x->get_Artist(),x->get_qualification(),x->get_Path_name()) ;
            this->temp_Path.push_back(x->get_Path_name()) ;
        }
        this->libary_change = false ;
        thread_1.get() ;
    }
        Temp_Info =  temp_Infoma ;
    return  ;

    }
}
void MainWindow::UI_Libary_setting()
{
    ui->quickWidget_3->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_3->setAttribute(Qt::WA_TranslucentBackground);
    ui->quickWidget_3->setClearColor(Qt::transparent);
    ui->quickWidget_3->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget_3->setSource(QUrl("qrc:/Libary_list_of_music.qml") );
    ui->quickWidget_3->show();    
    auto  obj =  ui->quickWidget_3->rootObject()  ;
    ui->quickWidget_3->rootContext()->setContextProperty("w",this);
    //ADD_artist(QVariant)

    connect(this ,  SIGNAL(Set_List_Path_name_Libary(QVariant , QVariant , QVariant , QVariant,QVariant)) , obj , SLOT(set_list_path_name(QVariant , QVariant , QVariant , QVariant,QVariant)));
    connect(this ,  SIGNAL(clear_libary_Music(QVariant)) , obj , SLOT(clear(QVariant)));
    connect(this ,  SIGNAL(ADD_artist(QVariant)) , obj , SLOT(add_Artist(QVariant)));
    connect(this ,  SIGNAL(clear_artist_list()) , obj , SLOT(clear_artist()));
    connect(this ,  SIGNAL(add_music_artist(QVariant , QVariant , QVariant , QVariant,QVariant)) , obj , SLOT(add_music_artist(QVariant , QVariant , QVariant , QVariant,QVariant)));
    connect(this ,  SIGNAL(clear_Artist_music()) , obj , SLOT(clear_Artist_music()));

}

void MainWindow::Insert_into_Artist_list(Infomation*artist)
{   
              auto it =  Artist.find(artist->get_Artist());
              if(it != Artist.end()) {
                  it->second.push_back(artist) ;
              }
              else if(Artist.size() == 0 || it == Artist.end()) {
                  QVector<Infomation*> vec ;
                  vec.push_back(artist) ;
                  this->Artist.insert({artist->get_Artist(),vec}) ;
              }
              return ;
}
