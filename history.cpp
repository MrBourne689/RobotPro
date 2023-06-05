#include <QtCharts>         // 导入QtCharts所有的头文件，也可以单独导入某一个

// 引入qchart命名空间（注意：如果是在ui中提升为QChartView，
// 则QT_CHARTS_USE_NAMESPACE一定要放在#include "ui_widget.h"前面，否则编译会失败）
QT_CHARTS_USE_NAMESPACE


#include "history.h"
#include "ui_history.h"
#include "QDebug"
#pragma execution_character_set("utf-8")

QString history::pdfname = " ";


history::history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    //主窗口背景颜色及字体颜色
    //this->setStyleSheet("color:#0bbdc2;background-color:#141626");
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
    //创建数据库并连接
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
    //创建student表
    QSqlQuery sql_query;

    QString str_sql = "";

//    str_sql = "create table student (time1 text,time2 text unique,speed double,BatteryVoltage double,RobotTemperature double,CH4Value double,O2Value double,H2SValue double,NH3Value double,Temperature double,Humidity double)";
//    str_sql = "create table student (time1 varchar(256),time2 varchar(256) unique,speed varchar(256),BatteryVoltage varchar(256),RobotTemperature varchar(256),CH4Value varchar(256),O2Value varchar(256),H2SValue varchar(256),NH3Value varchar(256),Temperature varchar(256),Humidity varchar(256))";
    str_sql = "create table student (id int primary key,time1 text,time2 text unique,"
              "speed double,BatteryVoltage double,RobotTemperature double,"
              "CH4Value double,O2Value double,H2SValue double,NH3Value double,"
              "Temperature double,Humidity double,xvalue double)";
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"创建student表失败！！"<< sql_query.lastError();
    }
    else
    {
        qDebug()<<"创建student表成功";

    }

}

history::~history()
{
    delete ui;
}

void history::showall()
{
    QSqlQuery sql_query;
    QString str_sql = "";
//    str_sql = "create table student (time1 varchar(256),time2 varchar(256) unique,speed varchar(256),BatteryVoltage varchar(256),RobotTemperature varchar(256),CH4Value varchar(256),O2Value varchar(256),H2SValue varchar(256),NH3Value varchar(256),Temperature varchar(256),Humidity varchar(256))";
    str_sql = "create table student (id int primary key,time1 text,time2 text unique,"
              "speed double,BatteryVoltage double,RobotTemperature double,"
              "CH4Value double,O2Value double,H2SValue double,NH3Value double,"
              "Temperature double,Humidity double,xvalue double)";
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"创建student表失败！！"<< sql_query.lastError();
    }
    else
    {
        qDebug()<<"创建student表成功";

    }

    //查询结果
    str_sql = "select * from student";
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        //qDebug()<<"查询结果如下：";
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        while(sql_query.next())
        {
            QString str_time = sql_query.value(1).toString();
            QString str_time2 = sql_query.value(2).toString();
            qDebug()<<str_time2;
            str_time2 = QDateTime::fromString(str_time2,"yyyyMMddhhmmss").toString("hh.mm.ss");
            qDebug()<<str_time2;
            QString str_speed = sql_query.value(3).toString();
            QString str_BatteryVoltage = sql_query.value(4).toString();
            QString str_RobotTemperature = sql_query.value(5).toString();
            QString str_CH4Value = sql_query.value(6).toString();
            QString str_O2Value = sql_query.value(7).toString();
            QString str_H2SValue = sql_query.value(8).toString();
            QString str_NH3Value = sql_query.value(9).toString();
            QString str_Temperature = sql_query.value(10).toString();
            QString str_Humidity = sql_query.value(11).toString();
            QString str_weiyi = sql_query.value(12).toString();

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
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 11, new QTableWidgetItem(str_weiyi));

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
    str_sql = "select distinct time1 from student";
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
//关闭事件
void history::closeEvent(QCloseEvent * event)
{
//    数据库关闭
        QSqlDatabase database;
        if (QSqlDatabase::contains("qt_sql_default_connection"))
        {
            database = QSqlDatabase::database("qt_sql_default_connection");
            database.close();
            qDebug() << "Database closed successfully";
        }
        else
        {
            qDebug() << "no database";
        }
}
void history::paintchart(){
    QSqlQuery query;
    if(ui->widget->layout()){
        clcgrid(ui->widget->layout());
    }
    delete  ui->widget->layout();
    if(ui->widget_2->layout()){
        clcgrid(ui->widget_2->layout());
    }
    delete  ui->widget_2->layout();

    if(ui->widget_4->layout()){
        clcgrid(ui->widget_4->layout());
    }
    delete  ui->widget_4->layout();
    if(ui->widget_6->layout()){
        clcgrid(ui->widget_6->layout());
    }
    delete  ui->widget_6->layout();
    QDateTime temp_1 = ui->dateTimeEdit->dateTime();
    QDateTime temp_2 = ui->dateTimeEdit_2->dateTime();
    QString str_1 = temp_1.toString("yyyyMMddhhmmss");
    QString str_2 = temp_2.toString("yyyyMMddhhmmss");
    QString sql = QString("select * from student where time2>='%1' and time2<='%2'").arg(str_1).arg(str_2);
    if(!query.exec(sql))
    {
        qDebug()<<query.lastError().text();
    }
    series_1 = new QLineSeries(this);
    series_2 = new QLineSeries(this);
    series_3 = new QLineSeries(this);
    series_4 = new QLineSeries(this);

    series_5 = new QLineSeries(this);
    series_6 = new QLineSeries(this);

    series_7 = new QLineSeries(this);

    series_8 = new QLineSeries(this);

    series_9 = new QLineSeries(this);
    while(query.next()){
        QSqlRecord record = query.record();
        //气体浓度数据
        QDateTime x_data = QDateTime::fromString(record.value("time2").toString(),"yyyyMMddhhmmss");
        int y_data = record.value(7).toString().toInt() ;
        int y_data_1 = record.value("O2Value").toString().toInt() ;
        int y_data_2 = record.value("H2SValue").toString().toInt() ;
        int y_data_3 = record.value("NH3Value").toString().toInt() ;

        int y_data_4 = record.value("Temperature").toString().toInt();
        int y_data_5 = record.value("Humidity").toString().toInt();

        int y_data_6 = record.value("RobotTemperature").toString().toInt();

        int y_data_7 = record.value("BatteryVoltage").toString().toInt();

        int y_data_8 = record.value("speed").toString().toInt();
        series_1->append(x_data.toMSecsSinceEpoch(),y_data);
        series_2->append(x_data.toMSecsSinceEpoch(),y_data_1);
        series_3->append(x_data.toMSecsSinceEpoch(),y_data_2);
        series_4->append(x_data.toMSecsSinceEpoch(),y_data_3);

        series_5->append(x_data.toMSecsSinceEpoch(),y_data_4);
        series_6->append(x_data.toMSecsSinceEpoch(),y_data_5);

        series_7->append(x_data.toMSecsSinceEpoch(),y_data_6);
        series_8->append(x_data.toMSecsSinceEpoch(),y_data_7);
        series_9->append(x_data.toMSecsSinceEpoch(),y_data_8);

        series_1->setName("CO2");
        series_1->setPointsVisible(true);
        series_1->setVisible(true);
        series_2->setName("O2浓度");
        series_2->setPointsVisible();
        series_3->setName("H2S浓度");
        series_3->setPointsVisible();
        series_4->setName("NH3浓度");
        series_4->setPointsVisible();
        series_5->setName("现场温度");
        series_5->setPointsVisible(true);
        series_6->setName("现场湿度");
        series_6->setPointsVisible(true);
        series_7->setName("机器人腔体温度");
        series_7->setPointsVisible(true);
        series_8->setName("电池电压");
        series_8->setPointsVisible(true);
        series_9->setName("机器人运行速度");
        series_9->setPointsVisible(true);
    }
    if(ui->checkBox->isChecked()){
        chaetlayout = new QGridLayout;
        chart = new QChart;
        chart->setTitle("CH4-O2-H2S-NH3浓度值");
        axisX = new QDateTimeAxis;
        axisY = new QValueAxis;
        axisX->setRange(temp_1,temp_2);
        axisX->setTickCount(6);
        axisX->setFormat("MM-dd hh:mm:ss");
        axisX->setTitleText("time"); //设置X坐标名字
        axisY->setTitleText("data");
        axisY->setTickCount(11);
        axisY->setRange(0,10);
        chart->addAxis(axisX , Qt::AlignBottom);
        chart->addAxis(axisY , Qt::AlignLeft);
        chartview = new QChartView(chart);
        chaetlayout->addWidget(chartview);
        chart->addSeries(series_1);
        chart->addSeries(series_2);
        chart->addSeries(series_3);
        chart->addSeries(series_4);
        series_1->attachAxis(axisX);
        series_1->attachAxis(axisY);
        series_2->attachAxis(axisX);
        series_2->attachAxis(axisY);
        series_3->attachAxis(axisX);
        series_3->attachAxis(axisY);
        series_4->attachAxis(axisX);
        series_4->attachAxis(axisY);
        showpoint(series_1);
        showpoint(series_2);
        showpoint(series_3);
        showpoint(series_4);
        ui->widget->setLayout(chaetlayout);
    }
    if(ui->checkBox_2->isChecked()){
        chaetlayout1 = new QGridLayout;
        chart1 = new QChart;
        chart1->setTitle("现场温度与现场湿度值与机器人腔体温度");
        axisX1 = new QDateTimeAxis;
        axisY1 = new QValueAxis;
        axisX1->setRange(temp_1,temp_2);
        axisX1->setTickCount(6);
        axisX1->setFormat("MM-dd hh:mm:ss");
        axisX1->setTitleText("time"); //设置X坐标名字
        axisY1->setTitleText("data");
        axisY1->setTickCount(11);
        axisY1->setRange(0,10);
        chart1->addAxis(axisX1 , Qt::AlignBottom);
        chart1->addAxis(axisY1 , Qt::AlignLeft);
        chart1->addSeries(series_5);
        chart1->addSeries(series_6);
        chart1->addSeries(series_7);
        series_5->attachAxis(axisX1);
        series_5->attachAxis(axisY1);
        series_6->attachAxis(axisX1);
        series_6->attachAxis(axisY1);
        series_7->attachAxis(axisX1);
        series_7->attachAxis(axisY1);
        chartview1 = new QChartView(chart1);
        chaetlayout1->addWidget(chartview1);
        ui->widget_2->setLayout(chaetlayout1);
        showpoint(series_5);
        showpoint(series_6);
    }
//    if(ui->checkBox_3->isChecked())
//    {
//        chaetlayout2 = new QGridLayout;
//        chart2 = new QChart;
//        chart2->setTitle("机器人腔体温度");
//        axisX2 = new QDateTimeAxis;
//        axisY2 = new QValueAxis;
//        axisX2->setRange(temp_1,temp_2);
//        axisX2->setTickCount(6);
//        axisX2->setFormat("MM-dd hh:mm:ss");
//        axisX2->setTitleText("time"); //设置X坐标名字
//        axisY2->setTitleText("data");
//        axisY2->setTickCount(11);
//        axisY2->setRange(0,10);
//        chart2->addAxis(axisX2 , Qt::AlignBottom);
//        chart2->addAxis(axisY2 , Qt::AlignLeft);
//        chart2->addSeries(series_7);
//        series_7->attachAxis(axisX2);
//        series_7->attachAxis(axisY2);
//        chartview2 = new QChartView(chart2);
//        chaetlayout2->addWidget(chartview2);
//        ui->widget_4->setLayout(chaetlayout2);
//        showpoint(series_7);
//    }
    if(ui->checkBox_3->isChecked())
    {
        chaetlayout3 = new QGridLayout;
        chart3 = new QChart;
        chart3->setTitle("电池电压");
        axisX3 = new QDateTimeAxis;
        axisX3->setTickCount(6);
        axisY3 = new QValueAxis;
        axisX3->setRange(temp_1,temp_2);
        axisX3->setFormat("MM-dd hh:mm:ss");
        axisX3->setTitleText("time"); //设置X坐标名字
        axisY3->setTitleText("数据");
        axisY3->setTickCount(11);
        axisY3->setRange(0,10);
        chart3->addAxis(axisX3 , Qt::AlignBottom);
        chart3->addAxis(axisY3 , Qt::AlignLeft);
        chartview3 = new QChartView(chart3);
        chaetlayout3->addWidget(chartview3);
        chart3->addSeries(series_8);
        series_8->attachAxis(axisX3);
        series_8->attachAxis(axisY3);
        ui->widget_4->setLayout(chaetlayout3);
        showpoint(series_8);
    }
    if(ui->checkBox_5->isChecked())
    {
        chaetlayout4 = new QGridLayout;
        chart4 = new QChart;
        chart4->setTitle("机器人运行速度");
        axisX4 = new QDateTimeAxis;
        axisX4->setTickCount(6);
        axisY4 = new QValueAxis;
        axisX4->setRange(temp_1,temp_2);
        axisX4->setFormat("MM-dd hh:mm:ss");
        axisX4->setTitleText("time"); //设置X坐标名字
        axisY4->setTitleText("数据");
        axisY4->setTickCount(11);
        axisY4->setRange(0,10);
        chart4->addAxis(axisX4 , Qt::AlignBottom);
        chart4->addAxis(axisY4 , Qt::AlignLeft);
        chartview4 = new QChartView(chart4);
        chaetlayout4->addWidget(chartview4);
        chart4->addSeries(series_9);
        series_9->attachAxis(axisX4);
        series_9->attachAxis(axisY4);
        ui->widget_6->setLayout(chaetlayout4);
        showpoint(series_9);

    }
}
void history::clcgrid(QLayout *layout){
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        ///setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(nullptr);
        }else if(child->layout()){
           clcgrid(child->layout());
        }
        delete child;
    }
}
//void history::on_pushButton_clicked()
//{
//    for (int i = 0;i<=30;i++) {
//        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//        int test =qrand()%10;
//        int test1 =qrand()%10;
//        int test2 =qrand()%10;
//        int test3 =qrand()%10;
//        int test4 =qrand()%10;
//        int test5 =qrand()%10;
//        int test6 =qrand()%10;
//        int test7 =qrand()%10;
//        int test8 =qrand()%10;
//        int test9 =qrand()%10;
//        QDateTime current_date_time =QDateTime::currentDateTime();
//        QString str_1 =current_date_time.toString("yyyy.MM.dd");
//        QString str_2 = current_date_time.toString("yyyyMMddhhmmss");
//        QString a1=QString::number(test);
//        QString a2=QString::number(test1);
//        QString a3=QString::number(test2);
//        QString a4=QString::number(test3);
//        QString a5=QString::number(test4);
//        QString a6=QString::number(test5);
//        QString a7=QString::number(test6);
//        QString a8=QString::number(test7);
//        QString a9=QString::number(test8);
//        makerecord(str_1,str_2,a1,a2,a3,a4,a5,a6,a7,a8,a9);
//        Sleep(1000);
//    }

//}

void history::on_pushButton_2_clicked()
{
    paintchart();
}
void history::makerecord(QString time_nyr, QString time_sf, QString xinxi_1, QString xinxi_2, QString xinxi_3, QString xinxi_4, QString xinxi_5,QString xinxi_6,QString xinxi_7,QString xinxi_8,QString xinxi_9)
{
    QString str_sql= QString("insert into student(time1,time2,speed,BatteryVoltage,RobotTemperature,CH4Value,O2Value,H2SValue,NH3Value,Temperature,Humidity) values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11')")
            .arg(time_nyr).arg(time_sf).arg(xinxi_1).arg(xinxi_2).arg(xinxi_3).arg(xinxi_4).arg(xinxi_5).arg(xinxi_6).arg(xinxi_7).arg(xinxi_8).arg(xinxi_9);
    QSqlQuery query;
    if(!query.exec(str_sql))
    {
        qDebug()<<query.lastError().text();
    };
}


void history::on_pushButton_3_clicked()
{
    showall();
}
void history::showpoint(QLineSeries *pos){
    QObject::connect(pos, &QLineSeries::hovered, [=](const QPointF &point, bool state)mutable{

            QPointF tempPoint(point.x(), qRound(point.y()));
            QList<int> yList;
            for (int i=0; i<pos->points().size(); ++i)
            {
                yList.append(qRound(pos->points().at(i).y()));
            }
            qDebug()<<point.y()<<point.x();
            QString y = QString::number(point.y(),'f',1);
            int max = *(std::max_element(yList.begin(),yList.end()));
            int min = *(std::min_element(yList.begin(),yList.end()));
            if(state){
                if(point.y() > max || point.y() < min){
                    return ;
                }
                QDateTime datatime;
                datatime = QDateTime::fromMSecsSinceEpoch(point.x());
                QString x = datatime.toString("yyyy-MM-dd hh:mm:ss");
                qDebug()<<datatime;
                QString y = QString::number(point.y(),'f',1);
                if(pos->name()==""){
                    QToolTip::showText(QCursor::pos(),QString("x=%1,y=%2").arg(x).arg(y));
                }
                else {
                    QToolTip::showText(QCursor::pos(),QString("x=%1,%2=%3").arg(x).arg(pos->name()).arg(y));
                }
            }
});
}

void history::on_pushButton_4_clicked()
{
    QDir dir;
    QString currerntDir = dir.currentPath();
    QString dir_str = currerntDir+"/PDF/";
    if(!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
    }
//    if(!pdfFile.open(QIODevice::WriteOnly|QIODevice::Append))
//    {
//        QMessageBox::warning(this,tr("write File"),tr("Cannot open file:\n%1").arg(pdfname));
//        return;
//    }
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString str_1 =current_date_time.toString("yyyy.MM.dd");
    QString filename = dir_str+str_1+".pdf";
    QFile pdfFile(filename);//输出文件名

    if(!pdfFile.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this,tr("write File"),tr("Cannot open file:\n%1").arg("d:\\test.pdf"));
            return;
        }
    QPdfWriter *pdfWriter = new QPdfWriter(&pdfFile);               //实例化QPdfWriter 可以设置PDF文件的一些参数
    pdfWriter->setPageSize(QPagedPaintDevice::A4);                  //设置纸张为A4纸 210 x 297
    pdfWriter->setResolution(QPrinter::ScreenResolution);           //设置分辨率
    pdfWriter->setPageMargins(QMarginsF(40, 40, 40, 40));//设置页边距 顺序是:左上右下



    int count = 0;
    QList<int>list;
    QList<int>list_win;
    list.clear();
    list_win.clear();
    if(ui->checkBox->isChecked()){
        count+=1;
        QWidget *snder = ui->widget;
        qDebug()<<snder->pos().x()<<snder->geometry().x()<<snder->geometry().x()+this->geometry().x();
        list.append(snder->pos().x());
        list.append(snder->pos().y());
        list_win.append(snder->pos().x()+this->geometry().x());
        list_win.append(snder->pos().y()+this->geometry().y());
        list.append(ui->widget->rect().width());
        list.append(ui->widget->rect().height());
        qDebug()<<ui->widget->rect().height()<<ui->widget->rect().width();
        list_win.append(ui->widget->rect().width());
        list_win.append(ui->widget->rect().height());
    }
    if(ui->checkBox_2->isChecked()){
        count+=1;
        QWidget *snder1 = ui->widget_2;
        list.append(snder1->pos().x());
        list_win.append(snder1->pos().x()+this->geometry().x());
        list.append(snder1->pos().y());
        list_win.append(snder1->pos().y()+this->geometry().y());
        list.append(ui->widget_2->rect().width());
        list.append(ui->widget_2->rect().height());
        list_win.append(ui->widget_2->rect().width());
        list_win.append(ui->widget_2->rect().height());
    }
    if(ui->checkBox_3->isChecked()){
        count+=1;
        QWidget *snder2 = ui->widget_4;
        list.append(snder2->pos().x());
        list.append(snder2->pos().y());
        list_win.append(snder2->pos().x()+this->geometry().x());
        list_win.append(snder2->pos().y()+this->geometry().y());
        list.append(ui->widget_4->rect().width());
        list.append(ui->widget_4->rect().height());
        list_win.append(ui->widget_4->rect().width());
        list_win.append(ui->widget_4->rect().height());
    }
    if(ui->checkBox_5->isChecked()){
        count+=1;
        QWidget *snder4 = ui->widget_6;
        list.append(snder4->pos().x());
        list.append(snder4->pos().y());
        list_win.append(snder4->pos().x()+this->geometry().x());
        list_win.append(snder4->pos().y()+this->geometry().y());
        list.append(ui->widget_6->rect().width());
        list.append(ui->widget_6->rect().height());
        list_win.append(ui->widget_6->rect().width());
        list_win.append(ui->widget_6->rect().height());
    }
    int n=count;
    QPainter painter_pixmap;
    painter_pixmap.begin(pdfWriter);
    QRect rect = painter_pixmap.viewport();

    int scale_width = rect.width()/ui->widget->rect().width();
    int scale_height = rect.height()/ui->widget->rect().height();
    int bias = rect.height()-ui->widget->rect().height()*scale_height;
    scale_height = scale_height/n;
    qDebug()<<scale_width<<scale_height;
//    painter_pixmap.scale(scale_width, scale_height);
    if(scale_width>=scale_height){
        painter_pixmap.scale(scale_height, scale_height);
    }
    else{
        painter_pixmap.scale(scale_width, scale_width);
    }
    bias = bias/n;
    for(int i = 0 ; i<count ;i++){
        QRect rectangle(list[i*4],list[i*4+1],list[i*4+2],list[i*4+3]);
        qDebug()<<list[i*4]<<list[i*4+1]<<list[i*4+2]<<list[i*4+3];
        QString str = QString("photo%1").arg(QString::number(i));
        QPixmap pixmap = QWidget::grab(rectangle);
        if(!QWidget::grab(rectangle).save(dir_str+str+".png","png")){
            QMessageBox::information(this,"warnning","failed");
        };
//        QPixmap pixmap1(dir_str+str);
        painter_pixmap.drawPixmap(0,i*(ui->widget->rect().height()+bias),pixmap);
//        painter_pixmap.drawPixmap(0,i*(pixmap1.height()+bias1),pixmap1);
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}
