#include "process_bar.h"
#include "ui_process_bar.h"
#include<QVariant>
#include<QDebug>
Process_bar::Process_bar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Process_bar)
{
    ui->setupUi(this);
    this->Set_Page() ;
    QWidget::setWindowTitle("Save");
}
void Process_bar::Set_Size(int SIZE)
{
    this->Size =  SIZE ;
    return ;
}

void Process_bar::Set_Page()
{
    QPixmap background("E:/dowload/color-background.png") ;
    background.scaled(this->size() ,Qt::IgnoreAspectRatio) ;
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

Process_bar::~Process_bar()
{
    delete ui;
}

void Process_bar::percent_change(double t )
{
  qDebug() << t << endl ;
  ui->progressBar->setValue((t/this->Size)*100) ;
  if(t == this->Size){
      this->accept() ;
  }

}
