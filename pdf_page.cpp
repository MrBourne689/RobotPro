#include <QtCharts>         // 导入QtCharts所有的头文件，也可以单独导入某一个

// 引入qchart命名空间（注意：如果是在ui中提升为QChartView，
// 则QT_CHARTS_USE_NAMESPACE一定要放在#include "ui_widget.h"前面，否则编译会失败）
QT_CHARTS_USE_NAMESPACE

#include "pdf_page.h"
#include "ui_pdf_page.h"

pdf_page::pdf_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pdf_page)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowIcon(QIcon(":/images/icon.png"));
}

pdf_page::~pdf_page()
{
    delete ui;
}

void pdf_page::initChart_p1()//CH4 O2 H2S NH3
{
    //QLineSeries* series = new QLineSeries();         // 创建一个折线图series

    QSplineSeries *series1 = new QSplineSeries();        // 创建一个曲线图series
    QSplineSeries *series2 = new QSplineSeries();        // 创建一个曲线图series
    QSplineSeries *series3 = new QSplineSeries();        // 创建一个曲线图series
    QSplineSeries *series4 = new QSplineSeries();        // 创建一个曲线图series

    QChart* chart = ui->chartView->chart();     // 获取QchartView内置的chart
    chart->removeAllSeries();//清除即可， 重要操作,QChart刷新的必要操作
    chart->setTitle("CH4-O2-H2S-NH3浓度值");            // 设置标题


    QSqlQuery sql_query;
    QString str_sql = "";


    QList<QPointF> points1;
    QList<QPointF> points2;
    QList<QPointF> points3;
    QList<QPointF> points4;
    QList<QPointF> points_safety;
    QCategoryAxis *axisX = new QCategoryAxis;
    //QCategoryAxis *axisY = new QCategoryAxis;

    //查询结果
    QList<QTableWidgetItem*> items = ui->tableWidget_2->selectedItems();
    if(!items.empty()){
        int row = ui->tableWidget_2->selectedItems()[0]->row();
        QString row_text = ui->tableWidget_2->item(row,0)->text();
        str_sql = "select * from student where time1 = '"+row_text+"'";
    }
    else{
        str_sql = "select * from student";
    }

    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        double i = 0;
        while(sql_query.next())
        {
            QString str_time2 = sql_query.value(2).toString();

            double str_CH4Value = sql_query.value(6).toDouble();
            double str_O2Value = sql_query.value(7).toDouble();
            double str_H2SValue = sql_query.value(8).toDouble();
            double str_NH3Value = sql_query.value(9).toDouble();

            if((i+1) == no ){
                ui->lineEdit->setText(str_time2);
                ui->lineEdit_3->setText(QString::number(i+1));
                if(ui->tableWidget->selectedItems()[0]->column()==5){
                    ui->lineEdit_2->setText(QString::number(str_CH4Value));
                    ui->label_2->setText("CH4浓度");
                }
                else if(ui->tableWidget->selectedItems()[0]->column()==6){
                    ui->lineEdit_2->setText(QString::number(str_O2Value));
                    ui->label_2->setText("O2浓度");
                }
                else if(ui->tableWidget->selectedItems()[0]->column()==7){
                    ui->lineEdit_2->setText(QString::number(str_H2SValue));
                    ui->label_2->setText("H2S浓度");
                }
                else if(ui->tableWidget->selectedItems()[0]->column()==8){
                    ui->lineEdit_2->setText(QString::number(str_NH3Value));
                    ui->label_2->setText("NH3浓度");
                }
            }



            axisX->append(str_time2, i);

            points1.append(QPointF(i, str_CH4Value));    //添加数据
            points2.append(QPointF(i, str_O2Value));    //添加数据
            points3.append(QPointF(i, str_H2SValue));    //添加数据
            points4.append(QPointF(i, str_NH3Value));    //添加数据
            points_safety.append(QPointF(i, 25));    //添加数据
            i++;
        }
    }
    series1->setName("CH4浓度值");
    series2->setName("O2浓度值");
    series3->setName("H2S浓度值");
    series4->setName("NH3浓度值");

    series1->replace(points1);
    series2->replace(points2);
    series3->replace(points3);
    series4->replace(points4);

    chart->addSeries(series1);                   // 将创建好的折线图series添加进chart中
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);

    series1->setPointsVisible(true);//使点变得明显
    series2->setPointsVisible(true);//使点变得明显
    series3->setPointsVisible(true);//使点变得明显
    series4->setPointsVisible(true);//使点变得明显

    chart->createDefaultAxes();                 // 基于已添加到图表中的series为图表创建轴。以前添加到图表中的任何轴都将被删除。



    //qDebug()<<"points2:"<<points_safety;
    QSplineSeries *series_safety = new QSplineSeries();
    series_safety->setName("预警线");
    series_safety->replace(points_safety);
    chart->addSeries(series_safety);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 50);
    axisY->setTickCount(7);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Value");     //设置坐标标题
    chart->setAxisY(axisY, series1);
    chart->setAxisY(axisY, series2);
    chart->setAxisY(axisY, series3);
    chart->setAxisY(axisY, series4);
    chart->setAxisY(axisY, series_safety);


    //axisX->setRange(0, 20);
    //axisX->setTickCount(21);
    axisX->setLabelFormat("%.2f");
    axisX->setLabelsAngle(45);
    axisX->setLabelsColor(Qt::blue);
    axisX->setLabelsEditable(true);
    axisX->setTitleText("时间");     //设置坐标标题
    chart->setAxisX(axisX, series1);
    chart->setAxisX(axisX, series2);
    chart->setAxisX(axisX, series3);
    chart->setAxisX(axisX, series4);
    chart->setAxisX(axisY, series_safety);

    ui->chartView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿
}
void pdf_page::initChart_p2()//现场温度 湿度
{
    QSplineSeries *series1 = new QSplineSeries();        // 创建一个曲线图series
    QSplineSeries *series2 = new QSplineSeries();        // 创建一个曲线图series

    QChart* chart = ui->chartView->chart();     // 获取QchartView内置的chart
    chart->removeAllSeries();//清除即可， 重要操作,QChart刷新的必要操作
    chart->setTitle("现场温度与现场湿度值");

    QSqlQuery sql_query;
    QString str_sql = "";


    QList<QPointF> points1;
    QList<QPointF> points2;

    QList<QPointF> points_safety;
    QCategoryAxis *axisX = new QCategoryAxis;
    //QCategoryAxis *axisY = new QCategoryAxis;

    //查询结果
    QList<QTableWidgetItem*> items = ui->tableWidget_2->selectedItems();
    if(!items.empty()){
        int row = ui->tableWidget_2->selectedItems()[0]->row();
        QString row_text = ui->tableWidget_2->item(row,0)->text();
        str_sql = "select * from student where time1 = '"+row_text+"'";
    }
    else{
        str_sql = "select * from student";
    }
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        double i = 0;
        while(sql_query.next())
        {
            QString str_time2 = sql_query.value(2).toString();

            double str_Temperature = sql_query.value(10).toDouble();
            double str_Humidity = sql_query.value(11).toDouble();

            if((i+1) == no && ui->tableWidget->selectedItems()[0]->column()==9){
                ui->lineEdit->setText(str_time2);
                ui->lineEdit_2->setText(QString::number(str_Temperature));
                ui->lineEdit_3->setText(QString::number(i+1));
                ui->label_2->setText("现场温度");
            }
            if((i+1) == no && ui->tableWidget->selectedItems()[0]->column()==10){
                ui->lineEdit->setText(str_time2);
                ui->lineEdit_2->setText(QString::number(str_Humidity));
                ui->lineEdit_3->setText(QString::number(i+1));
                ui->label_2->setText("现场湿度");
            }

            axisX->append(str_time2, i);
            points1.append(QPointF(i, str_Temperature));
            points2.append(QPointF(i, str_Humidity));

            points_safety.append(QPointF(i, 25));
            i++;
        }
    }
    series1->setName("现场温度");
    series2->setName("现场湿度");

    series1->replace(points1);
    series2->replace(points2);

    chart->addSeries(series1);
    chart->addSeries(series2);
    series1->setPointsVisible(true);//使点变得明显
    series2->setPointsVisible(true);//使点变得明显

    chart->createDefaultAxes();


    QSplineSeries *series_safety = new QSplineSeries();
    series_safety->setName("预警线");
    series_safety->replace(points_safety);
    chart->addSeries(series_safety);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 50);
    axisY->setTickCount(7);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Value");     //设置坐标标题
    chart->setAxisY(axisY, series1);
    chart->setAxisY(axisY, series2);
    chart->setAxisY(axisY, series_safety);


    //axisX->setRange(0, 20);
    //axisX->setTickCount(21);
    axisX->setLabelFormat("%.2f");
    axisX->setLabelsAngle(45);
    axisX->setLabelsColor(Qt::blue);
    axisX->setLabelsEditable(true);
    axisX->setTitleText("时间");     //设置坐标标题
    chart->setAxisX(axisX, series1);
    chart->setAxisX(axisX, series2);
    chart->setAxisX(axisY, series_safety);

    ui->chartView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿
}
void pdf_page::initChart_p3()//机器人运行速度
{
    QSplineSeries *series1 = new QSplineSeries();        // 创建一个曲线图series

    QChart* chart = ui->chartView->chart();     // 获取QchartView内置的chart
    chart->removeAllSeries();//清除即可， 重要操作,QChart刷新的必要操作
    chart->setTitle("机器人运行速度");

    QSqlQuery sql_query;
    QString str_sql = "";


    QList<QPointF> points1;

    QList<QPointF> points_safety;
    QCategoryAxis *axisX = new QCategoryAxis;

    //查询结果
    QList<QTableWidgetItem*> items = ui->tableWidget_2->selectedItems();
    if(!items.empty()){
        int row = ui->tableWidget_2->selectedItems()[0]->row();
        QString row_text = ui->tableWidget_2->item(row,0)->text();
        str_sql = "select * from student where time1 = '"+row_text+"'";
    }
    else{
        str_sql = "select * from student";
    }
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        double i = 0;
        while(sql_query.next())
        {
            QString str_time2 = sql_query.value(2).toString();

            double str_speed = sql_query.value(3).toDouble();

            if((i+1) == no){
                ui->lineEdit->setText(str_time2);
                ui->lineEdit_2->setText(QString::number(str_speed));
                ui->lineEdit_3->setText(QString::number(i+1));
                ui->label_2->setText("机器人运行速度");
            }
            axisX->append(str_time2, i);
            points1.append(QPointF(i, str_speed));

            points_safety.append(QPointF(i, 25));
            i++;
        }
    }
    series1->setName("机器人运行速度");

    series1->replace(points1);

    chart->addSeries(series1);
    series1->setPointsVisible(true);//使点变得明显


    chart->createDefaultAxes();

    QSplineSeries *series_safety = new QSplineSeries();
    series_safety->setName("预警线");
    series_safety->replace(points_safety);
    chart->addSeries(series_safety);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 50);
    axisY->setTickCount(7);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Value");     //设置坐标标题
    chart->setAxisY(axisY, series1);
    chart->setAxisY(axisY, series_safety);


    //axisX->setRange(0, 20);
    //axisX->setTickCount(21);
    axisX->setLabelFormat("%.2f");
    axisX->setLabelsAngle(45);
    axisX->setLabelsColor(Qt::blue);
    axisX->setLabelsEditable(true);
    axisX->setTitleText("时间");     //设置坐标标题
    chart->setAxisX(axisX, series1);
    chart->setAxisX(axisY, series_safety);

    chart->setTitle("机器人运行速度");
    ui->chartView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿
}
void pdf_page::initChart_p4()//电池电压
{

    QSplineSeries *series1 = new QSplineSeries();        // 创建一个曲线图series

    QChart* chart = ui->chartView->chart();     // 获取QchartView内置的chart
    chart->removeAllSeries();//清除即可， 重要操作,QChart刷新的必要操作
    chart->setTitle("电池电压");

    QSqlQuery sql_query;
    QString str_sql = "";


    QList<QPointF> points1;

    QList<QPointF> points_safety;
    QCategoryAxis *axisX = new QCategoryAxis;

    //查询结果
    QList<QTableWidgetItem*> items = ui->tableWidget_2->selectedItems();
    if(!items.empty()){
        int row = ui->tableWidget_2->selectedItems()[0]->row();
        QString row_text = ui->tableWidget_2->item(row,0)->text();
        str_sql = "select * from student where time1 = '"+row_text+"'";
    }
    else{
        str_sql = "select * from student";
    }
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        double i = 0;
        while(sql_query.next())
        {
            QString str_time2 = sql_query.value(2).toString();

            double str_BatteryVoltage = sql_query.value(4).toDouble();

            if((i+1) == no){
                ui->lineEdit->setText(str_time2);
                ui->lineEdit_2->setText(QString::number(str_BatteryVoltage));
                ui->lineEdit_3->setText(QString::number(i+1));
                ui->label_2->setText("电池电压");
            }

            axisX->append(str_time2, i);
            points1.append(QPointF(i, str_BatteryVoltage));

            points_safety.append(QPointF(i, 25));
            i++;
        }
    }
    series1->setName("电池电压");

    series1->replace(points1);

    chart->addSeries(series1);
    series1->setPointsVisible(true);//使点变得明显

    chart->createDefaultAxes();

    QSplineSeries *series_safety = new QSplineSeries();
    series_safety->setName("预警线");
    series_safety->replace(points_safety);
    chart->addSeries(series_safety);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 50);
    axisY->setTickCount(7);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Value");     //设置坐标标题
    chart->setAxisY(axisY, series1);
    chart->setAxisY(axisY, series_safety);


    //axisX->setRange(0, 20);
    //axisX->setTickCount(21);
    axisX->setLabelFormat("%.2f");
    axisX->setLabelsAngle(45);
    axisX->setLabelsColor(Qt::blue);
    axisX->setLabelsEditable(true);
    axisX->setTitleText("时间");     //设置坐标标题
    chart->setAxisX(axisX, series1);
    chart->setAxisX(axisY, series_safety);

    ui->chartView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿
}
void pdf_page::initChart_p5()//机器人腔体温度
{

    QSplineSeries *series1 = new QSplineSeries();        // 创建一个曲线图series

    QChart* chart = ui->chartView->chart();     // 获取QchartView内置的chart
    chart->removeAllSeries();//清除即可， 重要操作,QChart刷新的必要操作
    chart->setTitle("机器人腔体温度");

    QSqlQuery sql_query;
    QString str_sql = "";


    QList<QPointF> points1;

    QList<QPointF> points_safety;
    QCategoryAxis *axisX = new QCategoryAxis;

    //查询结果
    QList<QTableWidgetItem*> items = ui->tableWidget_2->selectedItems();
    if(!items.empty()){
        int row = ui->tableWidget_2->selectedItems()[0]->row();
        QString row_text = ui->tableWidget_2->item(row,0)->text();
        str_sql = "select * from student where time1 = '"+row_text+"'";
    }
    else{
        str_sql = "select * from student";
    }
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
    }
    else
    {
        double i = 0;
        while(sql_query.next())
        {
            QString str_time2 = sql_query.value(2).toString();

            double str_RobotTemperature = sql_query.value(5).toDouble();

            if((i+1) == no){
                ui->lineEdit->setText(str_time2);
                ui->lineEdit_2->setText(QString::number(str_RobotTemperature));
                ui->lineEdit_3->setText(QString::number(i+1));
                ui->label_2->setText("机器人腔体温度");
            }

            axisX->append(str_time2, i);
            points1.append(QPointF(i, str_RobotTemperature));

            points_safety.append(QPointF(i, 25));
            i++;
        }
    }
    series1->setName("机器人腔体温度");

    series1->replace(points1);

    chart->addSeries(series1);
    series1->setPointsVisible(true);//使点变得明显

    chart->createDefaultAxes();

    QSplineSeries *series_safety = new QSplineSeries();
    series_safety->setName("预警线");
    series_safety->replace(points_safety);
    chart->addSeries(series_safety);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 50);
    axisY->setTickCount(7);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText("Value");     //设置坐标标题
    chart->setAxisY(axisY, series1);
    chart->setAxisY(axisY, series_safety);


    //axisX->setRange(0, 20);
    //axisX->setTickCount(21);
    axisX->setLabelFormat("%.2f");
    axisX->setLabelsAngle(45);
    axisX->setLabelsColor(Qt::blue);
    axisX->setLabelsEditable(true);
    axisX->setTitleText("时间");     //设置坐标标题
    chart->setAxisX(axisX, series1);
    chart->setAxisX(axisY, series_safety);

    ui->chartView->setRenderHint(QPainter::Antialiasing);  // 设置抗锯齿


    chart->setTitle("机器人腔体温度");
    // 检查目录是否存在，若不存在则新建
    QDir dir;
    QString currerntDir = dir.currentPath();
    QString dir_str = currerntDir+"/PDF/";
    if(!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
    }
    query_time();
    pdfname = currerntDir+"/PDF/"+query_time1+"-"+query_time3+".pdf";

    QRect r1(QPoint(10,10),ui->chartView->size());

    initChart3();
    QPixmap pixmap3 = QWidget::grab(r1);
    render(&pixmap3);
    pixmap3.save(dir_str+"photo_机器人运行速度.png");
}
