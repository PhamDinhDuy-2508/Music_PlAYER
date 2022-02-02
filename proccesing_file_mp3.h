#ifndef PROCCESING_FILE_MP3_H
#define PROCCESING_FILE_MP3_H
#include<QString>
#include<QStringList>
#include<future>
#include<QVector>
#include<vector>
#include<QDebug>
#include<QFileInfo>
#include<QFileDevice>
#include<QDateTime>
#include<memory.h>
#include<map>
#include<QThread>
//#include<queue>
#include<map>
#include<QMediaPlayer>
#include<QMediaMetaData>
#include<list_mp3.h>
#include<QDir>
using namespace  std ;
using namespace QMediaMetaData;
enum class Random{
    Yes , No
};
class INFOR_File {
private  :
    QString Date_Time ;
    QString Name ;
    QString Title ;
    QString Path_name ;
    QString quality  ;
    QString ARtist ;
    QMediaPlayer*playlist ;
public :
    INFOR_File() = default ;
    INFOR_File(QString Date , QString Name , qint64 Time , QString Path , QString quality):
        Date_Time(Date) ,  Name(Name),  Path_name(Path) ,  quality(quality){
    }
    ~INFOR_File(){}
    void Set_name(QString name) {

        this->Name =  name ;
    }
    QString get_path(){
        return  this->Path_name ;
    }
    QString get_Name(){
        return this->Name ;
    }
    QString get_Path(){
        return  this->Path_name ;
    }
    void set_Title(QString TITLE) {
        this->Title =  TITLE;
    }
    void Set_quality(QString qual){
        this->quality =  qual ;
    }
    QString get_quality() {
        return this->quality ;
    }
    QString get_Arstist(){
        return this->ARtist ;
    }
    void Set_Artist(QString ARtist){
        this->ARtist =  ARtist ;
    }   
} ;
class LST_MP3{
private:
   QVector<QString>essential_list;
   QVector<QString> Random_list ;
public :
    LST_MP3()=default ;
    void Set_essential(QVector<QString> essential_list1) ;
    void Push_Random() ;
    void Set_Random(QVector<QString> essential_list1);
    QVector<QString>Get_essential_list(){
        return this->essential_list ;
    }
    QVector<QString>Get_Random_list(){
        return this->Random_list ;
   }
}  ;
class Proccesing_File_MP3
{
private :
QStringList Name_MUSIC_tail  ;
LST_MP3 List_Mp3 ;
future<void> Thread1  ;
vector<thread> Thread_Vector ;
shared_ptr<INFOR_File> LST;
QVector<shared_ptr<INFOR_File>> LIST_INFOR ;
map<QString,QString> Name_Path ;
QVector<QString> List_music ;
QString Top ;
map<QString, shared_ptr<INFOR_File>>map_INfor ;
shared_ptr<LIST_MP3>process ;
public:
    Proccesing_File_MP3();
    Proccesing_File_MP3(QStringList name) : Name_MUSIC_tail(name){
    }
   void check_File() {
        QString quality ;
        QString Model_name ;
        for(auto x : Name_MUSIC_tail) {
            QFileInfo info(x) ;
            quality = "" ;
            future<void> Thread_2 =  async(launch::async  , [this ,  info](){
                process =  make_shared<LIST_MP3>(info.fileName()) ;
                process->Set_name();
                LST->Set_name(process->Get_name()) ;
                LST->Set_Artist(process->Get_Artist());
                LST->set_Title(info.fileName()) ;
            });
            quality = '.' + info.completeSuffix() ;
           if(quality == ".mp3" ||  quality == ".flac") {
               LST =  make_shared<INFOR_File>("" ,  "",0 , info.absoluteFilePath() , quality);
               List_music.push_back(info.fileName()) ;
               Name_Path.insert({ info.fileName(), info.absoluteFilePath()  }) ;
               Thread_2.get() ;
               map_INfor.insert({info.fileName() , LST}) ;
               LIST_INFOR.push_back(LST);
               process.reset() ;
               }
        }
        Thread1 = async(launch::async,[this](){
            this->List_Mp3.Set_essential(List_music) ;
            this->List_Mp3.Push_Random() ;
        });
        return  ;
    }
   void Set_List_Music(QStringList List) {
       List_music.resize(0) ;
       for(auto x : List){
           QFileInfo info(x) ;
           List_music.push_back(info.fileName()) ;
      }
       this->List_Mp3.Set_essential(List_music) ;
       this->List_Mp3.Push_Random() ;

   }
   void Reset_all() {
       Name_MUSIC_tail.clear() ;
       Name_Path.clear() ;
   }
   void Set_name_music_tail(QStringList listMusic) {
       this->Name_MUSIC_tail =  listMusic ;
       Set_List_Music(Name_MUSIC_tail) ;
   }
   void Print_list() {
        for(auto x : Name_MUSIC_tail) {
        }
   }
   QStringList get_name_music_tail() {
        return this->Name_MUSIC_tail ;
   }
   QString get_path_by_name(QString name) {
       return Name_Path[name] ;
   }
   QString get_name(QString name) {
       return  map_INfor[name]->get_Name() ;
   }
   QString get_Author(QString name) {
       return map_INfor[name]->get_Arstist();
   }
   QString get_Qualification(QString name) {
       return map_INfor[name]->get_quality();
   }
   QVector<QString>  get_MP3()  {
       return this->List_music ;
   }
   bool check_empty() {
       if(Name_Path.empty()) {
           return true ;
       }
       else {
           return false ;
       }
   }      
  void Set_Random_Or_Essential(){
       Thread1.wait() ;//
       Thread1.get() ;           
   }  
  void Next() {
        Top =  *List_music.begin() ;
        this->List_music.pop_front();
        this->List_music.push_back(Top) ;
  }
  void Prev(){
      Top =  *List_music.rbegin() ;
      this->List_music.pop_back();
      this->List_music.push_front(Top) ;
  }
  void Print_Music(){
     return ;
  }
  void Connect_change(bool check){
      if(check == true){
          List_Mp3.Set_essential(this->List_music) ;
        this->List_Mp3.Push_Random() ;
        this->List_music = this->List_Mp3.Get_Random_list();
         this->Print_Music();
      }
      else {
          List_Mp3.Set_Random(this->List_music);
          this->List_music =  this->List_Mp3.Get_essential_list() ;
      }
      return;
  }
  QString Get_TOP(){
      return  *this->List_music.begin();
  }
  void Set_infor(QString infor1 , shared_ptr<INFOR_File>infor_class){
      QMediaPlayer*Music_player =  new QMediaPlayer()  ;
      Music_player->setMedia(QUrl::fromLocalFile(infor1)) ;
  }
  QString get_path(QString full_path){
      QFileInfo info(full_path) ;
       return  info.path();
  }
};
#endif // PROCCESING_FILE_MP3_H
