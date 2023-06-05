#include "camera_login.h"
#include "ui_camera_login.h"
#pragma execution_character_set("utf-8")
//相机
#include "QDebug"
#include "QString"
QString IP = "192.168.2.109";
QString Port = "37777";
QString Name = "admin";
QString Password = "admin123";

camera_login::camera_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera_login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/icon.png"));
    this->setWindowTitle("摄像头登录管理系统");
    ui->lineEdit->setText("192.168.2.109");
    ui->lineEdit_2->setText("37777");
    ui->lineEdit_3->setText("admin");
    ui->lineEdit_4->setText("admin123");
    //输入框不可编辑
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_2->setStyleSheet("color:grey");
    ui->lineEdit_3->setStyleSheet("color:grey");
    ui->lineEdit_4->setStyleSheet("color:grey");
    //点击提交按钮时，将信息保存到文件中
    QObject::connect(ui->pushButton,&QPushButton::clicked,this,&camera_login::saveMessage);
    //点击取消按钮时，关闭添加信息窗口
    QObject::connect(ui->pushButton_2,&QPushButton::clicked,this,&camera_login::close);
}

camera_login::~camera_login()
{
    delete ui;
}

void camera_login::saveMessage(){
    if(ui->lineEdit->text() !="" && ui->lineEdit_2->text()!="" && ui->lineEdit_3->text()!="" && ui->lineEdit_4->text()!=""){
        IP=ui->lineEdit->text();
        Port=ui->lineEdit_2->text();
        Name=ui->lineEdit_3->text();
        Password=ui->lineEdit_4->text();


        QFile file(file_name);
        file.open(QIODevice::WriteOnly|QIODevice::Append);
        QDataStream dataStr(&file);
        dataStr<<IP<<Port<<Name<<Password;
        file.close();
        this->close();
        emitCloseBox();


    }else{
        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }
}
void camera_login::emitCloseBox(){
    emit closeBox();
}
