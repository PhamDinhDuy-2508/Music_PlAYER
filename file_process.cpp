#include "file_process.h"
#include<iostream>
#include<QVector>
#include<QDir>
#include<QThread>
#include<QObject>
#include<map>
#include<QStringList>
#include"proccesing_file_mp3.h"
#include"file_process.h"
#include"database_process.h"
using namespace std ;

File_Process::File_Process()
{
    this->dir.setPath(file_name);

}
void File_Process::Load_data()
{
}
bool File_Process::check_directory_empty(){
   if(QDir(file_name).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0){
      return true ;
   }
   else {
       return false ;
   }
}
void File_Process::Open_directory(){
    if(check_directory_empty() == true ) {
        return ;
    }
    else {
        QDir directory(file_name) ;
        QStringList empty ;
        for(auto x :  QDir(file_name).entryList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
            file_and_copoment.insert({x , empty}) ;
            file_label.push_back(x) ;
        }
    }
    return ;
}
void File_Process::Create_Thread(QThread &thread)
{
    return ;
}

QMap<QString, QVector<QString> > File_Process::info_file()
{
    return this->load_reference ;
}

QVector<QString> File_Process::get_label()
{
    return this->file_label ;
}
void File_Process::get_element_in_playlist_folder_choice(QString File_name)
{
        QString file_choice =  file_name+"/"+File_name ;
        QDir directory(file_choice) ;
        if(QDir(file_choice).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() !=0) {
            for(auto x : QDir(file_choice).entryList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
                QString path_name  =  file_choice+"/"+x ;
                temp_list.push_back(path_name) ;
            }
            file_and_copoment[File_name] =  temp_list ;
            this->file_handle =  new Proccesing_File_MP3(temp_list) ;
            Thread_file_Filter =  async(launch::async ,  [this](){
                Infomation_of_file.resize( file_handle->get_MP3().size()) ;
                for(int i = 0; i < file_handle->get_MP3().size() ; i++) {
                    QString x =  file_handle->get_MP3()[i] ;
                    QString full_path = file_handle->get_path_by_name(x) ;
                    Infomation*info = new Infomation(x ,file_handle->get_name(x) , file_handle->get_Author(x) ,  file_handle->get_Qualification(x) ,full_path ) ;
                    List_Path.insert(file_handle->get_path(full_path)) ;
                    Infomation_of_file[i] = info ;
                }
                return ;

            }) ;
        }
        return ;
}

void File_Process::get_element_in_playlist_Database_Choice_choice(QString file_name)
{

}
void File_Process::Filter()
{
         if(check_Thread_join == false)  {
             this->Thread_file_Filter.wait() ;
             this->Thread_file_Filter.get();
             check_Thread_join = true ;
         }
         else {
            //.....///
         }
}


