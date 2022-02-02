#include "database_process.h"
#include"QtSql"
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QFileInfo>
#include<QVector>
#include<QSqlRecord>
#include"list_mp3.h"
#include<sort_custom.h>
#include<memory.h>
#include<QString>
#include<QDebug>
#include<QObject>
#include<QMessageBox>
#include<QDialog>
#include<QWidget>
void Database_process::Open_database(int i)
{
    database =  new QSqlDatabase() ;
    *database =  QSqlDatabase::addDatabase("QMYSQL") ;
    database->setHostName("127.0.0.1") ;
    database->setUserName("root") ;
    database->setPassword("") ;
    if(i == 0) {
    database->setDatabaseName("musicplaylist") ;
    }
    else if(i==1){
        database->setDatabaseName("libary_music_list") ;
    }
    else {
        database->setDatabaseName("artist") ;
    }
    this->stt_of_database =  i  ;
    database->open() ;


}

void Database_process::Close_datbase()
{
    if(stt_of_database == 0) {
        database->removeDatabase("musicplaylist") ;
    }
    else if(this->stt_of_database ==1) {
        database->removeDatabase("libary_music_list") ;
    }
    else {
        database->removeDatabase("artist") ;

    }
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    database->close() ;

}

void Database_process::Load_data_from_database()
{
    this->Load_data.clear() ;
    if(database->open()) {
        QSqlQuery sql(*database) ;
        sql.exec("SELECT Full_Path,Full_name,Name_of_music,Artist,Quality FROM " + this->name_of_Present_table );
        while(sql.next()) {
            Infomation*info_of_music = new Infomation( sql.value(1).toString() ,
                                                       sql.value(2).toString(),
                                                       sql.value(3).toString(),
                                                       sql.value(4).toString(),
                                                       sql.value(0).toString()) ;
            Load_data.push_back(info_of_music)  ;
        }
        Close_datbase() ;
    }
    return ;
}

void Database_process::Rename_Table(QString name)
{
    Open_database(0) ;
     QSqlQuery _query(*database)  ;
     QString rename_Code = "ALTER TABLE "+ Old_name+" RENAME TO "+ name  ;
     _query.prepare(rename_Code)  ;
     _query.exec();
    this->Old_name = name ;
   Close_datbase();

}

QVector<Infomation *> Database_process::get_Table_of_data()
{

    return this->Load_data ;
}

void Database_process::close()
{
    Close_datbase() ;
}

int Database_process::size_of_table()
{
    //Thread_1.get() ;
    return this->database->tables().size() ;
}

void Database_process::Set_Old_name(QString name)
{
    this->Old_name = name ;
}

void Database_process::delete_table(QString name)
{
    database->open() ;
    QSqlQuery Query(*database) ;
    QString Delete_code = "DROP TABLE "+ name   ;
    Query.prepare(Delete_code) ;
    Query.exec() ;
}

void Database_process::delete_music(QString name)
{
   database->open() ;
   QSqlQuery Query(*database) ;
   Query.prepare( "DELETE FROM "+this->name_of_Present_table+" WHERE Name_of_music ='"+name+"' ") ;
   Query.exec() ;
}

void Database_process::delete_all_music_in_table(QString name)
{
   database->open() ;
   QSqlQuery Query(*database) ;
   Query.prepare( "DELETE FROM "+this->name_of_Present_table) ;
   Query.exec() ;
   Close_datbase() ;
}

bool Database_process::check_datatabase_is_empty()
{
    Thread_1.get() ;
    if(this->List_of_table.size() == 0 ) {
        return true ;
    }
    else{
        return false ;
    }
}

Database_process::Database_process(int i)
{
    database =  new QSqlDatabase() ;

    *database =  QSqlDatabase::addDatabase("QMYSQL") ;
    database->setHostName("127.0.0.1") ;
    database->setUserName("root") ;
    database->setPassword("") ;
    if(i == 0) {
         database->setDatabaseName("musicplaylist") ;
    }
    else if ( i==1) {
         database->setDatabaseName("libary_music_list") ;
    }
    else {
         database->setDatabaseName("artist") ;
    }
    database->open() ;
    this->stt_of_database =  i ;
}

Database_process::~Database_process()
{
    delete database ;
    Close_datbase() ;
}
void Database_process::Create_table_name(QString name)
{
    database =  new QSqlDatabase() ;

    *database =  QSqlDatabase::addDatabase("QMYSQL") ;
    database->setHostName("127.0.0.1") ;
    database->setUserName("root") ;
    database->setPassword("") ;
    if(this->stt_of_database == 0) {
        database->setDatabaseName("musicplaylist") ;
    }
    else if(this->stt_of_database == 1) {
        database->setDatabaseName("libary_music_list") ;
    }
    else {
        database->setDatabaseName("artist") ;
    }

    if(database->open()) {
     QSqlQuery sql(*database) ;
    // this->name_of_Present_table =  name ;
        sql.prepare("CREATE TABLE IF NOT EXISTS "+name+" (Full_Path VARCHAR(256) , Full_name VARCHAR(256) , Name_of_music VARCHAR(256) ,Artist VARCHAR(256)  ,Quality VARCHAR(256))");
        sql.exec() ;
       qDebug() <<  sql.lastError() ;
    }
    Close_datbase() ;
     return ;
}
void Database_process::Add_data_into_database( Infomation* name)
{
    if(!database->isOpen()) {
        if(stt_of_database ==0 ) {
            Open_database(0) ;
        }
        else {
            Open_database(1) ;
        }
    }

    QSqlQuery Query(*database);

    if(database->isOpen()) {
        QString str = "INSERT INTO "+ this->name_of_Present_table+"(Full_Path,Full_name,Name_of_music,Artist,Quality)" ;
        QString path = "'" + name->get_Path_name() + "'" ;
        QString full_Name = "'" + name->get_Full_name() + "'" ;
        QString Name = "'" + name->get_Name() + "'" ;
        QString Artist = "'" + name->get_Artist() + "'" ;
        QString Qual = "'" + name->get_qualification() + "'" ;
        QString temp =  "VALUES (" + path +"," + full_Name+","+Name+","+Artist +"," + Qual+")";
        Query.prepare(str+temp) ;
        Query.exec() ;
    }
    else {
        int ret = QMessageBox::warning(this, tr("Warning"),
                                         tr("Cannot open database"),
                                         QMessageBox::Cancel );
           }
    Close_datbase() ;
    return ;
}
QStringList Database_process::list_table()
{
    Thread_1.get() ;
    return this->List_of_table ;
}

QString Database_process::set_database_name(QString name)
{
    this->name_of_Present_table =  name ;
    return " " ;
}

QString Database_process::get_name_of_Present_table()
{
    return this->name_of_Present_table;
}
bool Database_process::check_database_open()
{
    Open_database(stt_of_database) ;
    if(database->isOpen()){
        this->List_of_table.clear() ;
        QStringList tables  =  database->tables() ;
        Thread_1 =  async(launch::async , [=]() {
            for(auto x : tables) {
               this->List_of_table.push_back(x) ;
            }
        }) ;
        Close_datbase();
        return true ;
    }
    else {
        Close_datbase() ;
        return false ;
    }

}
