#ifndef MUSIC_PLAYLIST_CHOICE_H
#define MUSIC_PLAYLIST_CHOICE_H
#include<QDialog>
#include<QWidget>
#include<QObject>
#include<map>
#include<QVector>
#include"proccesing_file_mp3.h"
#include<sort_custom.h>
#include"file_process.h"
#include<QVariant>
#include<database_process.h>
#include<QStringList>
#include<future>
#include<mutex>
namespace Ui {
class Music_Playlist_choice;
}

class Music_Playlist_choice : public QDialog
{
    Q_OBJECT

public:
    explicit Music_Playlist_choice(QWidget *parent = nullptr);    
    explicit Music_Playlist_choice(QWidget *parent ,  QVector<Infomation*> Present_list ,Infomation*Present_Music);
    void open_database() ;
    void close_database() ;
    Q_INVOKABLE void signal_name_of_table(QVariant table_name) ;
    ~Music_Playlist_choice();
   QString get_table_name() ;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_progressBar_valueChanged(int value);

private:
    Ui::Music_Playlist_choice *ui;
    void Set_quick_widget() ;
    Database_process*database ;
    QStringList list_of_table ;
    shared_future<void> Thread1 ;
    QVector<Infomation*> present_list ;
    Infomation*present_music ;
    QString name_table ;
    bool one_music =  true ;
    bool all_music = true ;
    int Size ;

signals:
    void Add_Table_list(QVariant) ;
    void _Clear_list_signal(QVariant) ;
};

#endif // MUSIC_PLAYLIST_CHOICE_H
