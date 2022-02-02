#ifndef LIST_MP3_H
#define LIST_MP3_H
#include<QString>
#include<QDebug>
class LIST_MP3
{
private:
    QString file_name ;
    QString name_of_music ;
    QString Artist ;
public:
    LIST_MP3() ;
    LIST_MP3(QString name_file) : file_name(name_file){}
    void Set_file_name(QString name) {
        this->file_name =  name ;
    }
    void Set_name(){
        int count = 0 ;
        for(auto x : file_name) {
            if(count == 0 ){
                if(x == '_'){
                    count +=1 ;
                    continue ;
                }
                else {
                    name_of_music+= x ;
                }
            }
            if(count == 1){
                if(x == '_'){
                    count +=1 ;
                   break ;
                }
                else {
                    Artist+= x ;
                }
            }
        }
    }
    void Res_Name(){
        this->file_name = "";
    }
    void Res_Artis(){
        this->Artist = "";
    }
    QString Get_name()  {
        //qDebug() << this->name_of_music ;
        return this->name_of_music ;
    }
    QString Get_Artist(){
        //qDebug() << this->Artist ;
        return this->Artist ;
    }    
};

#endif // LIST_MP3_H
