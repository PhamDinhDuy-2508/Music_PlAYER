#ifndef NOFICATION_CLOSE_H
#define NOFICATION_CLOSE_H
#include"QVector"
#include <QDialog>
#include<iostream>
#include<sort_custom.h>
#include<string_view>
#include<QFileSystemModel>
#include<QFileSystemWatcher>
#include<QSet>
#include<future>
#include<QThread>
#include<thread>
#include<vector>
#include"proccesing_file_mp3.h"
#include"process_bar.h"
using namespace std ;
namespace Ui {
class Nofication_close;
}

class Nofication_close : public QDialog
{
    Q_OBJECT
public:
    explicit Nofication_close(QWidget *parent = nullptr);
    Nofication_close(QWidget *parent , QVector<Infomation*> iNFOMATION , QSet<QString>list_path ) ;
    ~Nofication_close();
    void Set_page() ;
    void Set_Mode() ;
    void Save_Mode(QString src , QString destiny) ;
    void Create_Folder() ;
    bool isMainThread();
signals :
    void Data_change(double) ;
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void Do_Work() ;
private:
    Ui::Nofication_close *ui;
    QSet<QString> List_Path ;
    QVector<Infomation*> Infomation_list ;
    QString Default_path ;
    QString file_save ;
    QFileSystemWatcher*FolderWatcher ;
    QString Date  ;
    QString name_path_save ;
    QThread*Thread1 ;
    int count = 0 ;
    vector<std::thread> Thread_Process ;
    Process_bar*Procss =   new Process_bar(this) ;

};

#endif // NOFICATION_CLOSE_H
