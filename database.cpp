#include "database.h"
#include "ui_database.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

database::database(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("qtsql");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if (ok){
       // QMessageBox::information(this, "infor", "success");
         qDebug()<<"success";
    }
    else {
        QMessageBox::information(this, "警告！", "DataBase Open Failed，Check whether there is a database or whether the parameters are correct!!!");
        qDebug()<<"error open database because"<<db.lastError().text();
        ui->label->setText(db.lastError().text());


    }
      //查询所有并放入表中
     SelectAllPushTableData();

     //初始化表格 格式
     ui->tableView->setColumnWidth(0,80);
     ui->tableView->setColumnWidth(1,150);
     ui->tableView->setColumnWidth(2,70);
     ui->tableView->setColumnWidth(3,70);
     ui->tableView->setColumnWidth(4,70);
     ui->tableView->setColumnWidth(5,70);
     ui->tableView->setColumnWidth(6,70);
     ui->tableView->setColumnWidth(7,70);

     /*初始化下拉框*/
     ui->comboBox->addItem("temp");
     ui->comboBox->addItem("humi");
     ui->comboBox->addItem("light");

     ui->comboBox->addItem("soil");
     ui->comboBox->addItem("mq2");
     ui->comboBox->addItem("rain");

     /*设置日期查询的初始化*/
     ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime().addSecs(0));
     ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(0));

     setFixedSize(750,650);

     setWindowTitle("——数据库管理平台——");
}


void database::SelectAllPushTableData(){
    tableModel = new QSqlQueryModel;//定义一个数据库模型，指定父对象

    QString strSelectData = "select * from qtdata";
    tableModel->setQuery(strSelectData);

    ui->tableView->setModel(tableModel);
}

void database::UpdataToDataBase(QString Stemp,QString Shumi,QString Slight,QString Ssoil,QString Smq2,QString Srain)
{
    float val[6];

    val[0] = Stemp.toFloat();
    val[1] = Shumi.toFloat();
    val[2] = Slight.toFloat();

    val[3] = Ssoil.toFloat();
    val[4] = Smq2.toFloat();
    val[5] = Srain.toFloat();

   // qDebug()<<val[0]<<" "<<val[1]<<" "<<val[2]<<" "<<val[3]<<" "<<val[4]<<" "<<val[5]<<" "<<" ";

    //插入
    insertData(val);

    //查询并全部显示
    SelectAllPushTableData();

}

//插入数据
bool database::insertData(float val[6])
{
    QSqlQuery query;

    //QDateTime currentTime = QDateTime::currentDateTime();

    QString stInsertData = "insert into qtdata values (?,?,?,?,?,?,?,?)";
    query.prepare(stInsertData);

    query.addBindValue(NULL);

    query.addBindValue(QDateTime::currentDateTime().addSecs(0).toString("yyyy-MM-dd hh:mm:ss"));

    query.addBindValue(val[0]);
    query.addBindValue(val[1]);
    query.addBindValue(val[2]);

    query.addBindValue(val[3]);
    query.addBindValue(val[4]);
    query.addBindValue(val[5]);


    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    return true;
}


//清空表
bool database::clearDBTable()
{
    QSqlQuery query;
    QString strClearDB = "delete from qtdata";
    query.prepare(strClearDB);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
    return true;
}


//日期查询
void database::SelectData()
{
    tableModel = new QSqlQueryModel;//定义一个数据库模型，指定父对象

    QString startTime = ui->dateTimeEdit->text();
    QString startTime2 = ui->dateTimeEdit_2->text();

    //查询操作
    QString strSelectData = "select *from qtdata where CurrenTime between '"+startTime+"' and '"+startTime2+"';";
    tableModel->setQuery(strSelectData);
    ui->tableView->setModel(tableModel);
}

database::~database()
{
    delete ui;
}


//退出
void database::on_exit_bt_clicked()
{
    this->close();
}

//查询按钮  ->查询指定日期
void database::on_select_data_bt_clicked()
{
    SelectData();
}

//显示所有
void database::on_displayAll_bt_clicked()
{
    SelectAllPushTableData();
}

//now
void database::on_now_bt_clicked()
{
    //当前时间
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime().addSecs(0));
}
//最近一天
void database::on_currDay_bt_clicked()
{
    //上一天
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(-3600*24));
   //当前时间
   ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime().addSecs(0));

   SelectData();
}
//最近三天
void database::on_currThDay_bt_clicked()
{
    //三天前天
   ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(-3600*24*3));
   //当前时间
   ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime().addSecs(0));

   SelectData();
}
//最近一周
void database::on_currWeek_bt_clicked()
{
    //七天前
   ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(-3600*24*7));
   //当前时间
   ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime().addSecs(0));

   SelectData();
}

//条件查询
void database::on_select_val_bt_clicked()
{
    //获取索引值
    QString strNum = ui->comboBox->currentText();

    //获取上下值
    QString downNum = ui->spinBox->text();
    QString upNum = ui->spinBox_2->text();

    //查询操作
    QString strSelectData = "select *from qtdata where "+strNum+" >= "+downNum+" && "+strNum+"<="+upNum+";";

    tableModel->setQuery(strSelectData);
    ui->tableView->setModel(tableModel);
}

//添加
/*
void database::on_add_bt_clicked()
{
    //插入数据
   // insertData();
    //查询并显示
    SelectAllPushTableData();
}*/
//清空表按钮
void database::on_clear_bt_clicked()
{
    clearDBTable();
    SelectAllPushTableData();
}
