#include "motion_control.h"
#include "ui_motion_control.h"
#include "mainwindow.h"
#include "QDebug"

Motion_control::Motion_control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Motion_control)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/icon.png"));
    this->setAttribute(Qt::WA_QuitOnClose,false);
    //主窗口背景颜色及字体颜色
    this->setStyleSheet("color:#0bbdc2;background-color:#141626");
    //按钮样式
    ui->groupBox->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->groupBox_3->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
}

Motion_control::~Motion_control()
{
    delete ui;
}
