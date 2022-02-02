#ifndef PROCESS_BAR_H
#define PROCESS_BAR_H

#include <QDialog>
#include<QVariant>

namespace Ui {
class Process_bar;
}

class Process_bar : public QDialog
{
    Q_OBJECT
public:
    explicit Process_bar(QWidget *parent = nullptr);
    void Set_Size(int SIZE) ;
    void Set_Page() ;
   ~Process_bar();

private:
    Ui::Process_bar *ui;
    int Size ;

public slots :
    void percent_change(double) ;

};
#endif // PROCESS_BAR_H
