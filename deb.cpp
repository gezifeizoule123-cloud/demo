#include "deb.h"
#include "mainwindow.h"
#include "ui_deb.h"
#include <QTextCodec>
#include <QMessageBox>
#include <string>


//发送缓冲区
QString strbuf;

Deb::Deb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deb)
{
    ui->setupUi(this);
    setFixedSize(520,400);

}

Deb::~Deb()
{
    delete ui;
}


void Deb::DisplayData(QString qstring){
    ui->rec_edi->appendPlainText(qstring);
}
void Deb::on_exit_bt_clicked()
{
    this->close();
}

//清除接受框
void Deb::on_clear_bt_clicked()
{
    ui->rec_edi->clear();
}
//清除发送框
void Deb::on_pushButton_2_clicked()
{
    ui->send_edi->clear();
}
//发送
void Deb::on_send_bt_clicked()
{
    MainWindow mainwindow ;
    strbuf = ui->send_edi->text() ;


     QString  str = "->";
     QString str2 = str.append(strbuf);
     ui->rec_edi->appendPlainText(str2);
     mainwindow.ttest();
}
