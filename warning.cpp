#include <QtCharts>         // 导入QtCharts所有的头文件，也可以单独导入某一个

// 引入qchart命名空间（注意：如果是在ui中提升为QChartView，
// 则QT_CHARTS_USE_NAMESPACE一定要放在#include "ui_widget.h"前面，否则编译会失败）
QT_CHARTS_USE_NAMESPACE

#include "warning.h"
#include "ui_warning.h"

#pragma execution_character_set("utf-8")

QString warning::query_time1 = " ";
QString warning::query_time2 = " ";
QString warning::query_time3 = " ";

warning::warning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::warning)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowIcon(QIcon(":/images/icon.png"));

    //设置列数
    ui->tableWidget->setColumnCount(12);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格内容不可编辑
    QStringList header;
    header<<"日期"<<"时间"<<"机器人运行速度"<<"电池电压"<<"机器人腔体温度"<<"CH4浓度值"<<"O2浓度值"<<"H2S浓度值"<<"NH3浓度值"<<"现场温度"<<"现场湿度"<<"位移值";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //ui->tableWidget->verticalHeader()->setHidden(true);//隐藏行号列s
    ui->tableWidget->setShowGrid(false);//隐藏标线

    ui->tableWidget_2->setColumnCount(1);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格内容不可编辑
    QStringList header2;
    header2<<"日期";
    ui->tableWidget_2->setHorizontalHeaderLabels(header2);
    ui->tableWidget_2->verticalHeader()->setHidden(true);//隐藏行号列
    ui->tableWidget_2->setShowGrid(false);//隐藏标线
    //连接数据库
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("HeFanRobot");
        database.setPassword("123456");
    }
    //判断数据库连接
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug()<<"DataBase open sucess!";
    }

    //当用户点击某个单元格时，更新列表中显示信息
    connect(ui->tableWidget_2,&QTableWidget::cellClicked,this,&warning::flushlistWidget2);

    showall();
    flushLineedit();
}

warning::~warning()
{
    delete ui;
}

//查询时间
void warning::query_time()
{
    QDateTime time= QDateTime::currentDateTime();//获取系统当前的时间
    query_time1 = time.toString("yyyy-MM-dd");//格式化日期
    query_time2 = time.toString("hh:mm:ss");//格式化时间
    query_time3 = time.toString("hh-mm-ss-a");//格式化时间
}

void warning::flushlistWidget2(int row){
    QSqlQuery sql_query;
    QString str_sql = "";

    QString row_text = ui->tableWidget_2->item(row,0)->text();

    str_sql = "select * from warning where time1 = '"+row_text+"'";

    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        while(sql_query.next())
        {
            QString str_time = sql_query.value(1).toString();
            QString str_time2 = sql_query.value(2).toString();
            QString str_speed = sql_query.value(3).toString();
            QString str_BatteryVoltage = sql_query.value(4).toString();
            QString str_RobotTemperature = sql_query.value(5).toString();
            QString str_CH4Value = sql_query.value(6).toString();
            QString str_O2Value = sql_query.value(7).toString();
            QString str_H2SValue = sql_query.value(8).toString();
            QString str_NH3Value = sql_query.value(9).toString();
            QString str_Temperature = sql_query.value(10).toString();
            QString str_Humidity = sql_query.value(11).toString();
            QString str_x = sql_query.value(12).toString();

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(str_time));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(str_time2));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(str_speed));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(str_BatteryVoltage));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(str_RobotTemperature));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5, new QTableWidgetItem(str_CH4Value));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 6, new QTableWidgetItem(str_O2Value));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 7, new QTableWidgetItem(str_H2SValue));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 8, new QTableWidgetItem(str_NH3Value));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 9, new QTableWidgetItem(str_Temperature));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 10, new QTableWidgetItem(str_Humidity));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 11, new QTableWidgetItem(str_x));

            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 9)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 10)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 11)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
        }
    }

}
//设定阈值
void warning::on_pushButton_clicked()
{
    if(ui->lineEdit->text() > ui->lineEdit_2->text() ||
            ui->lineEdit_3->text() > ui->lineEdit_4->text() ||
            ui->lineEdit_5->text() > ui->lineEdit_6->text() ||
            ui->lineEdit_7->text() > ui->lineEdit_8->text() ||
            ui->lineEdit_9->text() > ui->lineEdit_10->text() ||
            ui->lineEdit_11->text() > ui->lineEdit_12->text() ||
            ui->lineEdit_13->text() > ui->lineEdit_14->text() ||
            ui->lineEdit_15->text() > ui->lineEdit_16->text() ||
            ui->lineEdit_17->text() > ui->lineEdit_18->text()
            )
    {
        QMessageBox::warning(this,tr("查询失败"),tr("存在下限值大于上限值！"));
        return;
    }

    if(ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" ||
            ui->lineEdit_3->text()=="" || ui->lineEdit_4->text()=="" ||
            ui->lineEdit_5->text()=="" || ui->lineEdit_6->text()=="" ||
            ui->lineEdit_7->text()=="" || ui->lineEdit_8->text()=="" ||
            ui->lineEdit_9->text()=="" || ui->lineEdit_10->text()=="" ||
            ui->lineEdit_11->text()=="" || ui->lineEdit_12->text()=="" ||
            ui->lineEdit_13->text()=="" || ui->lineEdit_14->text()=="" ||
            ui->lineEdit_15->text()=="" || ui->lineEdit_16->text()=="" ||
            ui->lineEdit_17->text()=="" || ui->lineEdit_18->text()==""
            )
    {
        QMessageBox::warning(this,tr("查询失败"),tr("存在阈值为空！"));
        return;
    }

    QSqlQuery sql_query;
    QString str_sql = "";
    //查询最大id
    QString select_max_sql = "select max(id) from warningValue";
    int max_id = 0;
    sql_query.prepare(select_max_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            max_id = sql_query.value(0).toInt();
            qDebug() << QString("max id:%1").arg(max_id);
        }
    }

    //清除表
    str_sql = "DELETE FROM warningValue";
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"清除数据失败！！"<< sql_query.lastError();
    }
    else
    {
        //qDebug()<<"清除数据成功";

    }
    //插入数据
    query_time();

    str_sql = QString("insert into warningValue values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21)")
            .arg(1).arg(query_time1).arg(query_time2)
            .arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text())
            .arg(ui->lineEdit_3->text()).arg(ui->lineEdit_4->text())
            .arg(ui->lineEdit_5->text()).arg(ui->lineEdit_6->text())
            .arg(ui->lineEdit_7->text()).arg(ui->lineEdit_8->text())
            .arg(ui->lineEdit_9->text()).arg(ui->lineEdit_10->text())
            .arg(ui->lineEdit_11->text()).arg(ui->lineEdit_12->text())
            .arg(ui->lineEdit_13->text()).arg(ui->lineEdit_14->text())
            .arg(ui->lineEdit_15->text()).arg(ui->lineEdit_16->text())
            .arg(ui->lineEdit_17->text()).arg(ui->lineEdit_18->text())
            ;
    qDebug()<<"query_time1"<<query_time1;
    qDebug()<<"str_sql"<<str_sql;

    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"插入数据1失败！！"<< sql_query.lastError();
    }
    else
    {
        qDebug()<<"插入数据1成功";

    }

    QMessageBox::information(this,tr("完成"),tr("写入数据成功！"));
    showall();
}
void warning::showall(){
    QSqlQuery sql_query;
    QString str_sql = "";

    if(ui->lineEdit->text() > ui->lineEdit_2->text() ||
            ui->lineEdit_3->text() > ui->lineEdit_4->text() ||
            ui->lineEdit_5->text() > ui->lineEdit_6->text() ||
            ui->lineEdit_7->text() > ui->lineEdit_8->text() ||
            ui->lineEdit_9->text() > ui->lineEdit_10->text() ||
            ui->lineEdit_11->text() > ui->lineEdit_12->text() ||
            ui->lineEdit_13->text() > ui->lineEdit_14->text() ||
            ui->lineEdit_15->text() > ui->lineEdit_16->text() ||
            ui->lineEdit_17->text() > ui->lineEdit_18->text()
            )
    {
        QMessageBox::warning(this,tr("查询失败"),tr("存在下限值大于上限值！"));
        return;
    }

    str_sql = "select * from warning";

    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        while(sql_query.next())
        {
            QString str_time = sql_query.value(1).toString();
            QString str_time2 = sql_query.value(2).toString();
            QString str_speed = sql_query.value(3).toString();
            QString str_BatteryVoltage = sql_query.value(4).toString();
            QString str_RobotTemperature = sql_query.value(5).toString();
            QString str_CH4Value = sql_query.value(6).toString();
            QString str_O2Value = sql_query.value(7).toString();
            QString str_H2SValue = sql_query.value(8).toString();
            QString str_NH3Value = sql_query.value(9).toString();
            QString str_Temperature = sql_query.value(10).toString();
            QString str_Humidity = sql_query.value(11).toString();
            QString str_x = sql_query.value(12).toString();

            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(str_time));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(str_time2));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(str_speed));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(str_BatteryVoltage));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(str_RobotTemperature));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5, new QTableWidgetItem(str_CH4Value));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 6, new QTableWidgetItem(str_O2Value));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 7, new QTableWidgetItem(str_H2SValue));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 8, new QTableWidgetItem(str_NH3Value));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 9, new QTableWidgetItem(str_Temperature));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 10, new QTableWidgetItem(str_Humidity));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 11, new QTableWidgetItem(str_x));

            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 8)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 9)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 10)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
            ui->tableWidget->item(ui->tableWidget->rowCount()-1, 11)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
        }
    }
    //查询日期
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    str_sql = "select distinct time1 from warning";
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        //qDebug()<<"查询结果如下：";
        while(sql_query.next())
        {
            QString str_time = sql_query.value(0).toString();
            //qDebug()<<QString("time1:%1").arg(str_time);
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1, 0, new QTableWidgetItem(str_time));
            ui->tableWidget_2->item(ui->tableWidget_2->rowCount()-1, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置表格内容居中
        }
    }
}

void warning::flushLineedit(){
    QSqlQuery sql_query;
    QString str_sql = "";

    str_sql = "select * from warningValue";

    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        while(sql_query.next())
        {
            ui->lineEdit->setText(sql_query.value(3).toString());
            ui->lineEdit_2->setText(sql_query.value(4).toString());
            ui->lineEdit_3->setText(sql_query.value(5).toString());
            ui->lineEdit_4->setText(sql_query.value(6).toString());
            ui->lineEdit_5->setText(sql_query.value(7).toString());
            ui->lineEdit_6->setText(sql_query.value(8).toString());
            ui->lineEdit_7->setText(sql_query.value(9).toString());
            ui->lineEdit_8->setText(sql_query.value(10).toString());
            ui->lineEdit_9->setText(sql_query.value(11).toString());
            ui->lineEdit_10->setText(sql_query.value(12).toString());
            ui->lineEdit_11->setText(sql_query.value(13).toString());
            ui->lineEdit_12->setText(sql_query.value(14).toString());
            ui->lineEdit_13->setText(sql_query.value(15).toString());
            ui->lineEdit_14->setText(sql_query.value(16).toString());
            ui->lineEdit_15->setText(sql_query.value(17).toString());
            ui->lineEdit_16->setText(sql_query.value(18).toString());
            ui->lineEdit_17->setText(sql_query.value(19).toString());
            ui->lineEdit_18->setText(sql_query.value(20).toString());
        }
    }
}
////添加数据
//void warning::adddata()
//{
//    QSqlQuery sql_query;
//    QString str_sql = "";
//    //查询最大id
//    QString select_max_sql = "select max(id) from warning";
//    int max_id = 0;
//    sql_query.prepare(select_max_sql);
//    if(!sql_query.exec())
//    {
//        qDebug() << sql_query.lastError();
//    }
//    else
//    {
//        while(sql_query.next())
//        {
//            max_id = sql_query.value(0).toInt();
//            qDebug() << QString("max id:%1").arg(max_id);
//        }
//    }

//    //插入数据
//    //str_sql = "insert into student values(1,'wengmq',21)";
//    int ab =1;
//    for (int i=1; i<=100; ++i) {
//        query_time();

//        if(ab==1){
//            str_sql = QString("insert into warning values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,%13)")
//                    .arg(max_id+i).arg(query_time1).arg(query_time2).arg(21+1).arg(22+1).arg(23+1)
//                    .arg(24+1).arg(25+1).arg(26+1).arg(27+1).arg(28+1).arg(29+1).arg(6);
//            qDebug()<<"query_time1"<<query_time1;
//            qDebug()<<"str_sql"<<str_sql;

//            if(!sql_query.exec(str_sql))
//            {
//                qDebug()<<"插入数据失败！！"<< sql_query.lastError();
//            }
//            else
//            {
//                qDebug()<<"插入数据成功";

//            }
//            ab=0;
//        }


//        else{
//            str_sql = QString("insert into warning values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,%13)")
//                    .arg(max_id+i).arg("2022-07-13").arg(query_time2).arg(21-1).arg(22-1).arg(23-1)
//                    .arg(24-1).arg(25-1).arg(26-1).arg(27-1).arg(28-1).arg(29-1).arg(6);
//            qDebug()<<"query_time1"<<query_time1;
//            qDebug()<<"str_sql"<<str_sql;

//            if(!sql_query.exec(str_sql))
//            {
//                qDebug()<<"插入数据1失败！！"<< sql_query.lastError();
//            }
//            else
//            {
//                qDebug()<<"插入数据1成功";

//            }
//            ab=1;
//        }

//    }
//    QMessageBox::information(this,tr("完成"),tr("写入数据成功！"));

//    showall();
//}

//void warning::on_pushButton_2_clicked()
//{
//    adddata();
//}

void warning::on_pushButton_3_clicked()
{
    showall();
}
