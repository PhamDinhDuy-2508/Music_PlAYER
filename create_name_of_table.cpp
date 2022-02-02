#include "create_name_of_table.h"
#include "ui_create_name_of_table.h"

Create_name_of_table::Create_name_of_table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_name_of_table)
{
    ui->setupUi(this);
}

Create_name_of_table::Create_name_of_table(QWidget *parent, QString name_of_table):
    QDialog(parent),old_name(name_of_table) ,
    ui(new Ui::Create_name_of_table)
{
    ui->setupUi(this);
    database =  new Database_process(0) ;
    ui->lineEdit->setText(old_name);
    this->database->Set_Old_name(old_name) ;
    Thread1 = async(launch::async ,[=](){
        database->check_database_open() ;
    })  ;
}

Create_name_of_table::~Create_name_of_table()
{
    delete ui;
}

void Create_name_of_table::on_pushButton_clicked()
{

    if(ui->lineEdit_2->text() == "") {
        int ret = QMessageBox::warning(this, tr("My Application"),
                                         tr("Nameframe can't be empty.\n"
                                            "Do you want to keep the old name? ?"),
                                         QMessageBox::Ok  | QMessageBox::Cancel);        

    }
    else{
        Thread1.get() ;
        this->name_of_list_table =  database->list_table() ;

        bool check = true ;
        for(auto x : name_of_list_table) {
            if(ui->lineEdit_2->text() == x) {
                check =  false ;
                break ;
            }
        }
        if(check == false ) {
            int ret = QMessageBox::warning(this, tr("My Application"),
                                                     tr("Name already exists .\n"),
                                                     QMessageBox::Ok  | QMessageBox::Cancel);
        }
        else {

            qDebug() << this->name_of_list_table ;
            this->database->Rename_Table(ui->lineEdit_2->text()) ;
            this->database->close() ;
        }
    }
    accept() ;
}
