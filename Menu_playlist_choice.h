#ifndef ADD_ALL_MUSIC_INTO_PLAYLIST_H
#define ADD_ALL_MUSIC_INTO_PLAYLIST_H

#include <QDialog>

namespace Ui {
class Add_all_music_into_playlist;
}

class Add_all_music_into_playlist : public QDialog
{
    Q_OBJECT

public:
    explicit Add_all_music_into_playlist(QWidget *parent = nullptr);
    ~Add_all_music_into_playlist();

private:
    Ui::Add_all_music_into_playlist *ui;
};

#endif // ADD_ALL_MUSIC_INTO_PLAYLIST_H
