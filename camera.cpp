#include "camera.h"
#include "ui_camera.h"
#include <QHeaderView>
#pragma execution_character_set("utf-8")
camera::camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/icon.png"));
    this->setWindowTitle("IP登录管理系统");
    this->resize(1000,600);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置列数
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(7);
    //设置列表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"设备名称"<<"IP地址"<<"端口号"<<"用户名"<<"密码");
    //设置行表头
    ui->tableWidget->verticalHeader()->setVisible(false);
    //表格不可编辑
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 单列宽度
    ui->tableWidget->setColumnWidth(1, 150);
    flushTable();
    ////当用户点击某个单元格时，更新列表中显示信息
    //connect(ui->tableWidget,&QTableWidget::cellClicked,this,&camera::flushlistWidget);
    //当用户点击登录按钮时，进行摄像头登录
    connect(ui->pushButton,&QPushButton::clicked,this,&camera::camera_in);
    //当用户点击注销时，退出摄像头
    //connect(ui->pushButton_2,&QPushButton::clicked,this,&camera::deleteMessage);

    ui->tableWidget->setItem(6,0,new QTableWidgetItem("PLC"));
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("1#机器人"));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("2#机器人"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("1#摄像头"));
    ui->tableWidget->setItem(3,0,new QTableWidgetItem("2#摄像头"));
    ui->tableWidget->setItem(4,0,new QTableWidgetItem("3#摄像头"));
    ui->tableWidget->setItem(5,0,new QTableWidgetItem("4#摄像头"));
    // 设置只读
    for(int i = 0; i< 7;i++)
    {
        //ui->tableWidget->setItem(i,0,new QTableWidgetItem("1#机器人"));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem("37777"));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem("admin"));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem("admin123"));

        ui->tableWidget->item(i,0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,2)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,3)->setFlags(Qt::NoItemFlags);
        ui->tableWidget->item(i,4)->setFlags(Qt::NoItemFlags);
    }
}

camera::~camera()
{
    delete ui;
}
void camera::flushTable(){
    //更新表格内容前，要断开与 cellChanged 信号关联的所有槽，否则会导致程序闪退
    //disconnect(ui->tableWidget,&QTableWidget::cellChanged,0,0);
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QDataStream dataStr(&file);
    QString ip,port,name,password;
    //ui->tableWidget->setRowCount(0);
    int i = 0;
    while(!dataStr.atEnd()){
        //ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        dataStr>> ip >> port >> name >> password;
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(ip));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(port));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(name));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(password));
        i++;
    }
    file.close();
    update();
    //完成更新表格的任务后，重新关联与 cellChanged 相关的槽。
    //connect(ui->tableWidget,&QTableWidget::cellChanged,this,&camera::flushlistWidget);
}
void camera::camera_in(){
    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QDataStream dataStr(&file);

        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            for (int col = 1; col < ui->tableWidget->columnCount(); ++col) {
                QTableWidgetItem* item = ui->tableWidget->item(row, col);
                if (item) {
                    dataStr << item->text();
                } else {
                    dataStr << "";
                }
            }
        }

        file.close();
    }
    flushTable();
    QMessageBox::information(this,"完成","IP保存成功！");
    //this->close();
}
