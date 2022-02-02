#ifndef DATABASE_PROCESS_H
#define DATABASE_PROCESS_H
#include"QtSql"
#include<QSqlQuery>
#include<QSqlDatabase>
#include<iostream>
#include<set>
#include"QStringList"
#include<future>
#include<sort_custom.h>
#include<QMessageBox>
#include<QString>
class Database_process : public QDialog
{
private:
    QSqlDatabase *database ;
    QString music ;
    set<QString> list_table_name ;
    QString name_of_Present_table ;
    QStringList List_of_table ;
    QSqlQuery query ;
    shared_future<void> Thread_1 ;
    QVector<Infomation*> Load_data ;
    int stt_of_database ;
    QString Old_name ;
    QString new_name ;
public:
    Database_process(int i);
    ~Database_process() ;
    void Create_table_name(QString name) ;
    void Add_data_into_database( Infomation*name) ;
    QStringList list_table() ;
    QString set_database_name(QString name) ;
    QString get_name_of_Present_table() ;
    bool check_database_open() ;
    void Open_database(int i) ;
    void Close_datbase() ;
    void Load_data_from_database() ;
    void Rename_Table(QString name) ;
    QVector<Infomation *> get_Table_of_data() ;
    void close() ;
    int size_of_table() ;
    void Set_Old_name(QString name) ;
    void delete_table(QString name) ;
    void delete_music(QString name) ;
    void delete_all_music_in_table(QString name) ;
    bool check_datatabase_is_empty() ;



};

#endif // DATABASE_PROCESS_H
