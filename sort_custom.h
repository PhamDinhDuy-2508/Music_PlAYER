 #ifndef SORT_CUSTOM_H
#define SORT_CUSTOM_H
#include<iostream>
#include"QString"
#include"QStringList"
#include<QVector>
#include<memory>
#include<algorithm>
#include<utility>
#include<QPair>
#include<QVector>
#include<QDebug>
#include"QStack"
#include"QChar"
using namespace  std ;
class Infomation{
    QString Full_name ;
    QString Name  ;
    QString Artist ;
    QString qualification ;
    QString path_name ;
public :   
    Infomation(QString Fullname , QString name , QString artiArtistst , QString Quali , QString Path_name ){
        this->Full_name =  Fullname ;
        this->Artist = artiArtistst ;
        this->qualification = Quali ;
        this->Name =  name ;
        this->path_name =  Path_name ;
    }
    ~Infomation(){
        this->Full_name =  "" ;
        this->Artist = "" ;
        this->qualification = "" ;
        this->Name =  "" ;
    }
    Infomation &Move(Infomation && object) {
        this->Name =  object.Name ;
        this->Full_name =  object.Full_name ;
        this->Artist = object.Artist ;
        this->path_name =  object.path_name ;
        this->qualification = object.qualification ;
         object.Name = nullptr ;
         object.Full_name =  nullptr ;
         object.Artist =  nullptr ;
         object.qualification = nullptr ;
         object.path_name = nullptr ;
         return *this  ;
    }
    Infomation &Copy(Infomation & object) {
        this->Name =  object.Name ;
        this->Full_name =  object.Full_name ;
        this->Artist = object.Artist ;
        this->path_name =  object.path_name ;
        this->qualification = object.qualification ;
         return *this  ;
    }
    QString get_qualification() {
        return this->qualification ;
    }
    QString get_Artist() {
        return this->Artist ;
    }
    QString get_Name() {
        return this->Name ;
    }
    QString get_Full_name() {
        return this->Full_name ;
    }
    QString get_Path_name() {
        return this->path_name ;
    }
};
class SORT_custom
{
private:
   QVector<shared_ptr<Infomation>> info ;
public:

    SORT_custom();    
};
class ALPHA_Sort : public SORT_custom{
private:
    QVector<shared_ptr<Infomation>> info ;
    QVector<shared_ptr<Infomation>> resut;
    shared_ptr<Infomation> temp  ;
public:
    ALPHA_Sort(QVector<shared_ptr<Infomation>> Info):info(Info){}
    void Sort(){}
       /* sort(info.begin() , info.end(),[this]( shared_ptr<Infomation> &S1 ,  shared_ptr<Infomation> &S2){
            QPair<QChar,QChar> element ;
            if(S1->Name.size() > S2->Name.size()) {
                for(int i = 0; i < S2->Name.size() ; i++){
                    if(S1->Name[i]!= S2->Name[i]) {
                         element.first = S1->Name[i] ;
                         element.second =  S2->Name[i] ;
                         break ;
                    }
                }
                element.first = S1->Name[0] ;
                element.second =  S2->Name[0] ;
            }
            else if(S1->Name.size() < S2->Name.size()){
                for(int i = 0; i <S1->Name.size() ; i++){
                    if(S1->Name[i]!= S2->Name[i]) {
                        element.first = S1->Name[i] ;
                        element.second =  S2->Name[i] ;
                         break ;
                    }
                }
                element.first = S1->Name[0] ;
                element.second =  S2->Name[0] ;
            }
            else {
                for(int i = 0; i < S1->Name.size() ; i++){
                    if(S1->Name[i] != S2->Name[i]){
                        if(S1->Name[i]!= S2->Name[i]) {
                            element.first = S1->Name[i] ;
                            element.second =  S2->Name[i] ;
                             break ;
                        }
                    }
                }
                element.first = S1->Name[0] ;
                element.second =  S2->Name[0] ;

            }
            return element.first < element.second ;
        }) ;
    }*/
};
template<typename T> class Specification{
    private :
    typedef QVector<T*> Music ;
public :
    Specification() =  default ;
    virtual bool is_Satified(T*item) const =  0  ;
    virtual bool is_Filter_Satified(T*item , int STT ) const  = 0 ;
    ~Specification() =  default ;
} ;
class Fitler {
private :
    typedef QVector<Infomation*> infomation ;
    infomation result ;
    QStringList Path_name ;
    QStack<infomation> Stack ;
public :
    Fitler() =  default ;
    infomation fitler(Specification<Infomation>& specification , infomation all )  {
        result.resize(0) ;Path_name.clear() ;
        for(auto &x : all){
            if(specification.is_Satified(x)) {
                result.push_back(x) ;
                Path_name.push_back(x->get_Path_name()) ;
            }
        }
        return result ;
    }
    infomation Filter_Search(Specification<Infomation>& Specification ,  infomation all , int stt) {
        infomation result_Search ;
        for(auto &x :all ){
                if(Specification.is_Filter_Satified(x,stt) ) {
                    result_Search.push_back(x) ;
                               }
            }
        return  result_Search ;
    }
    QStringList get_path_name() {
        return this->Path_name ;
    }
    ~Fitler() {};
};
class Quality_Specification:public Specification<Infomation>{
private :
    QString Quality ;
public :
    Quality_Specification(QString Qual):Quality(Qual){}
    bool is_Satified(Infomation*item) const override{
        if(item->get_qualification() == Quality) {
            return true ;
        }
        else {
            return false ;
        }
    }
    bool is_Filter_Satified(Infomation*item,int STT)const override {
        return false ;
    }
    ~Quality_Specification(){}
};
class Name_Specification :public Specification<Infomation>{
    private :
    QString name ;
    QChar character ;
public :
    Name_Specification(QString Name):name(Name){}
    Name_Specification(QChar Name):character(Name){}
   bool is_Satified(Infomation*item) const override{
       if(item->get_Name() ==  name) {
           return true ;
       }
       else {
           return false ;
       }
   }
    bool is_Filter_Satified(Infomation*item,int STT)const override {
            if(item->get_Name().at(STT) == character ){
                return true ;
            }
            else  {
                return false ;
            }
   }
   ~Name_Specification(){}
} ;
class Artist_Specification:public Specification<Infomation>{
private:
    QString Artist ;
    QChar character ;
public :
    Artist_Specification(QString Art):Artist(Art) {}
    Artist_Specification(QChar Art):character(Art) {}
    bool is_Satified(Infomation *item) const override{
            if(item ->get_Artist() ==  Artist) {
                return true ;
            }
            else {
                return false ;
            }
    }
    bool is_Filter_Satified(Infomation*item , int STT )const override {
        if(item->get_Artist().at(STT) == character) {
            return true ;
        }
        else {
            return false ;
        }
    }
    ~Artist_Specification(){}
} ;
class Name_Qualitu_Specification:public Specification<Infomation>{
} ;
class Result {
private :
    QVector<Infomation*> all ;
    QVector<Infomation*> Quality ;
    QVector<Infomation*>  Name ;
    QVector<Infomation*>  Artist ;
    QStringList path_name ;
    QVector<Infomation*> Search ;
    QStack<QVector<Infomation*>>Stack ;
    Fitler fit ;
    QStack<QVector<Infomation*>> Stack_Fitler ;
    QStack<QChar> charac ;
public :
    Result(QVector<Infomation*> all_list) :  all(all_list) {
        Stack.push_back(all) ;
    }
    void Set_Stack_char( QStack<QChar> charac){

    }
    int size() {
        return this->all.size();
    }    
    void Set_path_name(QStringList list) {
        this->path_name = list  ;
    }
    void Pop_character() {
        charac.pop() ;
    }
    QStringList get_path_name() {
        return this->path_name ;
    }
    QVector<Infomation*> Quality_Fitler(QString qual) {
        Quality.resize(0) ;
        Quality_Specification _quality(qual) ;
         Quality = fit.fitler(_quality , all) ;
         path_name =  fit.get_path_name() ;
         return Quality;
    }
    QVector<Infomation*> Name_Fitler(QString name){
        Name_Specification _Name_filter(name) ;
        Name =  fit.fitler(_Name_filter , all) ;
        path_name =  fit.get_path_name() ;
       return Name ;
    }
    void Restart_Stack() {
       while(!Stack.empty()) {
           Stack.pop() ;
       }
        Stack.push_back(all) ;
    }
    QVector<Infomation*> Name_search_Filter(QChar name  , int size) {
          Name_Specification _Name_fitler(name) ;
          if(size < charac.size()) {
              charac.pop() ;
              Stack.pop() ;
          }
          else {
          charac.push(name) ;
            Search =  fit.Filter_Search(_Name_fitler , Stack.top(), charac.size()-1 ) ;
            Stack.push(Search) ;
          }
           return Stack.top() ;
    }

    void POP() {
        Stack.pop() ;
    }
    QVector<Infomation*>Artisit_search_Filter(QChar name  , int size){
            Artist_Specification _Artist_Filter(name) ;
            if(size < charac.size()) {
                charac.pop() ;
                Stack.pop() ;
            }
            else {
            charac.push(name) ;
              Search =  fit.Filter_Search(_Artist_Filter , Stack.top(), charac.size()-1 ) ;
              Stack.push(Search) ;
            }
             return Stack.top() ;
    }
    QVector<Infomation*> Top(){
        return this->Stack.top() ;
    }
    QVector<Infomation*> Artist_Fitler(QString Art){
       Artist_Specification _Artist_Fitler(Art) ;
      return fit.fitler(_Artist_Fitler , all) ;
    }
    ~Result(){};
} ;
#endif // SORT_CUSTOM_H
