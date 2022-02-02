 #ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<future>
#include<QListWidget>
#include<QWidget>
#include"QMultimedia"
#include"QMediaPlayer"
#include"proccesing_file_mp3.h"
#include"QtQml/qqml.h"
#include<QStack>
#include<QVariant>
#include<QString>
#include<mediaerr.h>
#include<sort_custom.h>
#include<future>
#include"memory.h"
#include"QCloseEvent"
#include <QSet>
#include"QThread"
#include"file_process.h"
#include"QtSql"
#include"database_process.h"
#include<music_playlist_choice.h>
#include<thread>
using namespace std ;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void View() ;
    void Set_Stack_Widget() ;
    void Set_Stack_Widget_Main() ;
    void Set_connect_Position_datatachange()  ;
    void Set_page() ;
    void Set_Time_0(quint64 time) ;
    QString Format_Time(quint64 Time) ;
    void Image_Qquick() ;
    void List_quick() ;
    void Set_label_Name(QString name) ;
    void Name_Music() ;    
    void Set_signal_Pause_Or_Play();
    void Set_infor(QString name);
    Q_INVOKABLE void connect_qml(const QString &name_of_music) ;
    Q_INVOKABLE int get_size(const int size) ;
    void Fitler(QString re_quire);    
    void Prsent_list(QVector<Infomation*> arg1 , QString signal) ;
    Q_INVOKABLE void text_Search_change(const QString &text,int signal)  ;
    Q_INVOKABLE QString combobox_Text(const QString &text) ;
    Q_INVOKABLE void _Get_element_in_file(QString file_name);
    Q_INVOKABLE void signal_add_new_playlist(bool bool_signal);
    Q_INVOKABLE void  check_and_get_List(QVariant x) ;
    Q_INVOKABLE void  rename_table(QVariant x) ;
    Q_INVOKABLE void  delete_table(QVariant x) ;
    Q_INVOKABLE void delete_music_playlist(QVariant x) ;
    Q_INVOKABLE void add_Music_in_playlist() ;
    Q_INVOKABLE void delete_in_main_list(QVariant x) ;
    Q_INVOKABLE void add_Music_into_playlist(QVariant x)  ;
    Q_INVOKABLE void reset_datbase(QVariant x)  ;
    Q_INVOKABLE void load_Music_all_from_libary(QVariant x);
    Q_INVOKABLE void play_music(QVariant , QVariant , QVariant , QVariant,QVariant) ;
    Q_INVOKABLE void add_list() ;
    Q_INVOKABLE void save_list() ;
    Q_INVOKABLE void delete_all() ;
    Q_INVOKABLE void save_music_in_playlist() ;

    Q_INVOKABLE void delete_music_in_libary(QVariant x) ;
    Q_INVOKABLE void delete_all_music_in_libary(QVariant x) ;
     Q_INVOKABLE void play_all() ;
    Q_INVOKABLE void load_into_libary() ;
    Q_INVOKABLE void signal_Artist_page() ;
    Q_INVOKABLE void signal_Artist(QVariant name) ;
    Q_INVOKABLE void back_signal();

    void Load_Table()  ;
    void Set_table_of_database() ;
    void UI_Libary_setting() ;
    void Insert_into_Artist_list(Infomation*) ;

protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_Browser_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void On_Duration_change(quint64 Duration) ;
    void On_Position_change(quint64 Position) ;
    void on_Play_or_Pause_clicked();
    void on_Volumn_valueChanged(int value);
    void on_Volum_button_clicked(bool checked) ;
    void on_Random_clicked();
    void Set_Pos(int Pos) ;
    void on_loop_clicked();
    void on_arrow_Prev_clicked();
    void on_Arrow_next_clicked();
    void on_Next_clicked();
    void on_Prev_clicked();
    void Play();
    void check_Finished(qint64 position) ;    
    void Metadatachanged() ;
    void OnMedia_changed(QMediaPlayer::MediaStatus status,QMediaPlayer *player );
    void Get_data_change(QMediaPlayer *player) ;
   // void Get_infomation(QVariant) ;
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void Set_Infomation_of_Music() ;
    /// Playlist Page
    void on_Favorite_clicked();
    void PlayList_page_Set() ;
    void OnPlayingWidget_Playlist() ;
    void on_Home_clicked();

    void on_Add_clicked();


    void on_Save_clicked();

    void on_Libary_clicked();




private:
    QMediaPlayer*Music_player ;
     QMediaPlayer* Infomusic ;
    QListWidget*mSingleClick_Item ;
    bool check_doubleclick ;
    future<void> check ;
    QString Present_music ;
    Ui::MainWindow *ui;
    Proccesing_File_MP3*MP3_Process ;
    QVector<QString>  LIS_MP3 ;
    bool count_play = false ;
    int Pos ;
    bool count_check =  false ;
    bool Random_check = false ;
    bool Loop_check =  false  ;
    bool check_Random = false ;
     int duration;
    future<void> Info_Thread;
    QStack<int> Stack_Next ;
    QStack<int> Stack_Prev ;
    QVector<map<QString,QString>> LIST_MUSIC ;
    QString TOP ;
    future<void> Get_info ;
    QMediaPlayer*media;
    QVector<Infomation*> Infoma ;
    QStack<QChar> Stack_step ;

    Result*Filter_Search;
    Result*Filter_Search_Table_playlist ;
    Result*Filter_Search_playlist ;

    QString Combobox_choice =  "Song" ;

    QVector<Infomation*> Table_list ;

    bool combobox_change =  false ;
    QVector<Infomation*> Search_Result ;
    QSet<QString> List_Path ;
    QThread*Thread1;
    shared_future<void> Thread_Process_file ;
    QVector<QString> data_file ;
    QVector<QString> test ;
    File_Process*control_Process ;
    QVector<Infomation*>Infomation_of_playlist ;
    Database_process*database ;
    bool check_file_change = false ;
    QVector<Infomation*> Present_list ;
    Infomation*Present_Music ;
    shared_future<void> Thread_for  ;
    shared_future<void> Thread_Path  ;
    QStringList Path_name ;
    void Browser_Process() ;
    Database_process*database_list_music ;
    QSqlTableModel*Model ;
    QVector<Infomation*>temp_Infoma ;
    QVector<Infomation*> Temp_Info ;
    QStringList temp_Path ;
    QStringList Present_path ;
    bool libary_change = false ;
    bool Playlist_change = false  ;
    map<QString , QVector<Infomation*>> Artist ;
   vector<std::thread> thread_artist ;
   QVector<QString> Artist_list ;



signals:
    void set_Duration(QVariant);
    void Set_pause(QVariant);
    void Set_List_Path_name(QVariant , QVariant , QVariant , QVariant) ;
    void Set_name_Music(QVariant) ;
    void get_signal_Pause_or_Play(QVariant) ;
    void Fitler_LST(QVariant , QVariant , QVariant , QVariant,QVariant,QVariant) ;
    void Get_signal_infomation(QVariant);
    void Combox_signal(QVariant) ;
    void clear_list_music(QVariant) ;
    void Search_field(QVariant , QVariant , QVariant , QVariant);
    void Get_size(QVariant) ;
    void Get_list_file(QVariant) ;
    void clear_list_model(QVariant) ;
    void clear_list_view(QVariant) ;
    void add_data_to_QML(QVariant , QVariant , QVariant , QVariant) ;
    void Search_field_table(QVariant ) ;
    void  Search_field_playlist(QVariant , QVariant , QVariant , QVariant ) ;
    void editingFinished() ;
    void Set_List_Path_name_Libary(QVariant , QVariant , QVariant , QVariant,QVariant) ;
    void clear_libary_Music(QVariant) ;
    void Play_all(QVariant)  ;
    void ADD_artist(QVariant) ;
    void clear_artist_list() ;
    void add_music_artist(QVariant , QVariant , QVariant , QVariant,QVariant) ;
    void clear_Artist_music() ;

#endif // MAINWINDOW_H
};
