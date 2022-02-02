#ifndef CREATE_NAME_OF_TABLE_H
#define CREATE_NAME_OF_TABLE_H

#include <QDialog>
#include<QString>
#include<database_process.h>
#include<future>

namespace Ui {
class Create_name_of_table;
}

class Create_name_of_table : public QDialog
{
    Q_OBJECT

public:
    explicit Create_name_of_table(QWidget *parent = nullptr);
    explicit Create_name_of_table(QWidget *parent , QString name_of_table);



    ~Create_name_of_table();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Create_name_of_table *ui;
    QString old_name ;
    QString new_name ;
    Database_process*database ;
    QStringList name_of_list_table ;
    shared_future<void> Thread1 ;
};

#endif // CREATE_NAME_OF_TABLE_H
