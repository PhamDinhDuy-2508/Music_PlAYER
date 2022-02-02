#include "proccesing_file_mp3.h"
#include<iostream>
#include<random>
#include<map>
#include<algorithm>
#include<QVector>
#include"QDebug"
using namespace std ;
Proccesing_File_MP3::Proccesing_File_MP3(){
}

void LST_MP3::Set_essential(QVector<QString> essential_list1){
   this->essential_list =  essential_list1 ;
        return  ;
}
void LST_MP3::Push_Random(){
    this->Random_list =  this->essential_list ;
    random_shuffle(this->Random_list.begin() , this->Random_list.end()) ;    

}

void LST_MP3::Set_Random(QVector<QString> essential_list1)
{
}

