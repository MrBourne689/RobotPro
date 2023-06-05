#ifndef WARNING_H
#define WARNING_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QtPrintSupport/QtPrintSupport>
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTime>
#include <windows.h>

namespace Ui {
class warning;
}

class warning : public QWidget
{
    Q_OBJECT

public:
    explicit warning(QWidget *parent = nullptr);
    ~warning();

    void query_time();//查询时间
    static QString query_time1;//年月日
    static QString query_time2;//时分秒
    static QString query_time3;//时分秒
    void flushlistWidget2(int row);//更新表格
    void flushLineedit();//更新输入框
    void showall();
    void adddata();

private slots:


    void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::warning *ui;

};

#endif // WARNING_H
