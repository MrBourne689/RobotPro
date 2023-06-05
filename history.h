#ifndef HISTORY_H
#define HISTORY_H

#include <QDateTimeAxis>
#include <QValueAxis>
#include <QWidget>
#include "robot_login.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QtPrintSupport/QtPrintSupport>
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QGridLayout>
#include <QChartView>
#include<QChart>
#include <QLineSeries>
#include <QPointF>
#include <QtSql/QSqlError>		// 数据库连接失败打印报错语句
#include <QtSql/QSqlQuery>		// 数据库操作（增删改查）
#include <QSqlRecord>
#include <Windows.h>

using namespace QtCharts;
namespace Ui {
class history;
}

class history : public QWidget
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

    void flushlistWidget();//更新表格
    void showall();//展示全部数据
    void clcgrid(QLayout*);
    void paintchart();
    void makerecord(QString time_nyr, QString time_sf, QString xinxi_1, QString xinxi_2, QString xinxi_3, QString xinxi_4, QString xinxi_5,QString xinxi_6,QString xinxi_7,QString xinxi_8,QString xinxi_9);

    void showpoint(QLineSeries *pos);
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartview;
    QChart *chart;

    QDateTimeAxis *axisX1;
    QValueAxis *axisY1;
    QChartView *chartview1;
    QChart *chart1;

    QDateTimeAxis *axisX2;
    QValueAxis *axisY2;
    QChartView *chartview2;
    QChart *chart2;

    QDateTimeAxis *axisX3;
    QValueAxis *axisY3;
    QChartView *chartview3;
    QChart *chart3;

    QDateTimeAxis *axisX4;
    QValueAxis *axisY4;
    QChartView *chartview4;
    QChart *chart4;

    QList<QPointF> mydata1;
    QLineSeries *series_1;
    QLineSeries *series_2;
    QLineSeries *series_3;
    QLineSeries *series_4;
    QLineSeries *series_5;
    QLineSeries *series_6;
    QLineSeries *series_7;
    QLineSeries *series_8;
    QLineSeries *series_9;


    QGridLayout *chaetlayout;
    QGridLayout *chaetlayout1;
    QGridLayout *chaetlayout2;
    QGridLayout *chaetlayout3;
    QGridLayout *chaetlayout4;



    int findlistmax(QList<int> list1);

    static QString pdfname;

private:
    Ui::history *ui;
    QSqlDatabase base1;
    QSqlDatabase base2;
protected :
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // HISTORY_H
