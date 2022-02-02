#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H
#include<iostream>
#include<QString>
#include<string_view>
#include<QDir>
#include<QVector>
#include<QMap>
#include<QDebug>
#include<QThread>
#include <QObject>
#include <QStringList>
#include"future"
#include<map>
#include"proccesing_file_mp3.h"
#include"sort_custom.h"
#include"database_process.h"
using namespace  std ;
class File_Process :public QObject
{
    Q_OBJECT
private :
   QString file_name  ;
    QStringList temp_list ;
   QMap<QString ,  QVector<QString>> load_reference ;
   QDir dir ;
   QVector<QString> file_label ;
   map<QString , QStringList> file_and_copoment;
   Proccesing_File_MP3*file_handle ;
   QVector<Infomation*> Infomation_of_file ;
   future<void> Thread_file_Filter ;
   bool check_Thread_join = false ;
   QSet<QString> List_Path ;
   Database_process*database ;
public:
    File_Process();
    File_Process(QString path_name):file_name(path_name){
        dir.setPath(file_name)   ;       
    }
    bool check_directory_empty() ;
    void Load_data() ;
    void Open_directory() ;
    void Create_Thread(QThread &thread) ;
    QMap<QString , QVector<QString>> info_file() ;
    QVector<QString> get_label() ;
    void get_element_in_playlist_folder_choice(QString file_name);
    void get_element_in_playlist_Database_Choice_choice(QString file_name) ;
    void Filter() ;
public slots :
    void Process() {
        Open_directory() ;
        return ;
    }
};
class Control : public QObject{
private :
    QThread File_Thread ;
    QString File_name ;
public :
    Control(QString file_name) : File_name(file_name){
      File_Process *_FILE_PROCESS =  new File_Process(File_name) ;
      _FILE_PROCESS->Create_Thread(File_Thread) ;
      _FILE_PROCESS->moveToThread(&File_Thread) ;
      File_Thread.start() ;
    }
    Control() = default ;
    ~Control(){
        File_Thread.wait() ;
        File_Thread.quit() ;
    }
};

#endif // FILE_PROCESS_H
