#ifndef CREATE_PLAYLIST_H
#define CREATE_PLAYLIST_H

#include <QDialog>

namespace Ui {
class Create_playlist;
}

class Create_playlist : public QDialog
{
    Q_OBJECT

public:
    explicit Create_playlist(QWidget *parent = nullptr);
    ~Create_playlist();
    QString get_name_table() ;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Create_playlist *ui;
};

#endif // CREATE_PLAYLIST_H
