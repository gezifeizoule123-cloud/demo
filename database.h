#ifndef DATABASE_H
#define DATABASE_H

#include <QWidget>

#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class database;
}

class database : public QWidget
{
    Q_OBJECT

public:
    explicit database(QWidget *parent = nullptr);
    ~database();


    //查询所有并放入表中
    void SelectAllPushTableData();
    bool insertData(float val[6]);
    bool clearDBTable();
    void SelectData();

    void UpdataToDataBase(QString Stemp,QString Shumi,QString Slight,QString Ssoil,QString Smq2,QString Srain);
    //table 类
    QSqlQueryModel *tableModel;

private slots:
    void on_exit_bt_clicked();


    void on_select_data_bt_clicked();

    void on_displayAll_bt_clicked();

    void on_now_bt_clicked();

    void on_currDay_bt_clicked();

    void on_currThDay_bt_clicked();

    void on_currWeek_bt_clicked();

    void on_select_val_bt_clicked();

    void on_clear_bt_clicked();

private:
    Ui::database *ui;
};

#endif // DATABASE_H
