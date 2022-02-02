#ifndef ADD_MUISIC_INTO_PLAYLIST_H
#define ADD_MUISIC_INTO_PLAYLIST_H

#include <QDialog>

namespace Ui {
class Add_muisic_into_Playlist;
}

class Add_muisic_into_Playlist : public QDialog
{
    Q_OBJECT

public:
    explicit Add_muisic_into_Playlist(QWidget *parent = nullptr);
    ~Add_muisic_into_Playlist();

private:
    Ui::Add_muisic_into_Playlist *ui;
};

#endif // ADD_MUISIC_INTO_PLAYLIST_H
