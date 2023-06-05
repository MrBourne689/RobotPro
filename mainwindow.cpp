#include <QtCharts>         // 导入QtCharts所有的头文件，也可以单独导入某一个

// 引入qchart命名空间（注意：如果是在ui中提升为QChartView，
// 则QT_CHARTS_USE_NAMESPACE一定要放在#include "ui_widget.h"前面，否则编译会失败）
QT_CHARTS_USE_NAMESPACE

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "time.h"
#include "QString"
#include "QTime"
#include <QHeaderView>
#include "robot_login.h"
//相机
#include "QDebug"
#include "QString"

#include <QFont>
#include <QPainter>
#include <QPixmap>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include <windows.h>

QImage Mimage;
QString Mfilename="./path.jpg";
int Mp_a=0;
int Z=0;
int MS=0;
int ML=0;
int MM;
double MN;
int guiji_m;

int Always_switch=1;// 总切换
int kozhi=0;
int plc_kozhi=0;
int speed=0;//电机转速
int heartbeat=0;//心跳包
int MainWindow::robot_bool=0;//判断是否连接了机器人，避免闪退
int MainWindow::plc_bool=1;//判断是否连接了plc，避免闪退
int MainWindow::robot_104=0;//控制字
int MainWindow::activeCheckboxCount = 0;// 获取当前选中的复选框个数

LLONG Login1;//相机1登录句柄
LLONG Login2;//相机2登录句柄
LLONG Login;//切换登录句柄

QString MainWindow::robot1_IP;
QString MainWindow::robot1_PORT;
QString MainWindow::robot1_USERNAME;
QString MainWindow::robot1_PASSWORD;
QString MainWindow::robot2_IP;
QString MainWindow::robot2_PORT;
QString MainWindow::robot2_USERNAME;
QString MainWindow::robot2_PASSWORD;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->checkBox_81->setVisible(false);
    c1->moveToThread(t1);
    c2->moveToThread(t2);
    r1->moveToThread(t3);

    ui->label_7->installEventFilter(this);

    ui->label_7->setStyleSheet("border-image: url(./path.jpg)");

    ui->label_7->setFixedSize(400,300);


    m_timer.setInterval(1000);
    m_timer.start();
    //qDebug()<<"我是定时器启动";
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));

    //创建坐标表
    QSqlQuery sql_query;

    QString str_sql = "";

    str_sql = "create table zuobiao (id int primary key,x int,y int,s int)";
    if(!sql_query.exec(str_sql))
    {
        //qDebug()<<"创建坐标表失败！！"<< sql_query.lastError();
    }
    else
    {
        //qDebug()<<"创建坐标表成功";

    }

    qRegisterMetaType<HWND>("HWND");

    HWND hWnd1 = (HWND)ui->frame1->winId();
    qDebug("hWnd1=%d", hWnd1);
    HWND hWnd2 = (HWND)ui->frame2->winId();

    connect(this,&MainWindow::send2,c1,&cam1::rev1);
    connect(this,&MainWindow::send,c1,&cam1::rev);
    connect(this,&MainWindow::send1,c1,&cam1::working);
    connect(ui->cam_Action,&QAction::triggered,this,[=]()
    {
        emit send(hWnd1);//发送视频显示控件句柄
        emit send1();//发送信号调用相机工作函数
        t1->start();//子线程启动
    });
    connect(c1,&cam1::send,this,&MainWindow::rev1);
    connect(ui->pushButton_8,&QPushButton::clicked,c1,&cam1::video);
    connect(ui->pushButton_7,&QPushButton::clicked,c1,&cam1::cvideo);

    connect(ui->action_cutcam,&QAction::triggered,this,[=]()
    {
        disconnect(this,&MainWindow::send2,c1,&cam1::rev1);
        disconnect(this,&MainWindow::send,c1,&cam1::rev);
        disconnect(this,&MainWindow::send1,c1,&cam1::working);
        disconnect(c1,&cam1::send,this,&MainWindow::rev1);
        disconnect(ui->pushButton_8,&QPushButton::clicked,c1,&cam1::video);
        disconnect(ui->pushButton_7,&QPushButton::clicked,c1,&cam1::cvideo);
        c1->cut1();
    });

    connect(this,&MainWindow::send2,c2,&cam2::rev1);
    connect(this,&MainWindow::send_w2,c2,&cam2::rev);
    connect(this,&MainWindow::send1,c2,&cam2::working);
    connect(ui->cam_Action,&QAction::triggered,this,[=]()
    {
        emit send_w2(hWnd2);//发送视频显示控件句柄
        emit send1();//发送信号调用相机工作函数
        t2->start();//子线程启动
    });
    connect(c2,&cam2::send,this,&MainWindow::rev2);

    connect(ui->action_cutcam,&QAction::triggered,this,[=]()
    {
        disconnect(this,&MainWindow::send2,c2,&cam2::rev1);
        disconnect(this,&MainWindow::send_w2,c2,&cam2::rev);
        disconnect(this,&MainWindow::send1,c2,&cam2::working);
        disconnect(c2,&cam2::send,this,&MainWindow::rev2);
        c2->cut2();
    });

    connect(this,&MainWindow::send2,r1,&rob1::rev1);
    connect(this,&MainWindow::send_rob,r1,&rob1::working);
    connect(ui->robot_Action,&QAction::triggered,this,[=]()
    {
        emit send_rob();//发送信号调用机器人工作函数
        t3->start();//子线程启动
    });
    connect(this,&MainWindow::send3,r1,&rob1::rev2);
    connect(this,&MainWindow::send_allin,r1,&rob1::allin);//送入一键上电值
    connect(this,&MainWindow::send5,r1,&rob1::rev3);
    connect(r1,&rob1::send_104,this,&MainWindow::get_104);//获取控制字
    connect(r1,&rob1::send_100,this,&MainWindow::get_100);//获取控制字
    connect(r1,&rob1::send_102,this,&MainWindow::get_102);//获取控制字
    connect(r1,&rob1::send_robot_connect_bool,this,&MainWindow::rec_robot_connect_bool);//获取机器人连接状态
    connect(this,&MainWindow::send6,r1,&rob1::rev4);
    connect(this,&MainWindow::send7,this,[=]()
    {
        connect(r1,&rob1::send_,this,&MainWindow::send_position);
    });
    connect(this,&MainWindow::send8,r1,&rob1::rev5);
    connect(this,&MainWindow::send9,r1,&rob1::rev6);
    connect(this,&MainWindow::send10,r1,&rob1::rev7);
    connect(this,&MainWindow::send11,r1,&rob1::rev8);
    connect(this,&MainWindow::send12,r1,&rob1::rev9);
    connect(this,&MainWindow::send13,r1,&rob1::rev10);
    connect(r1,&rob1::warning_signal,this,&MainWindow::warning_box);
    connect(r1,&rob1::xintiaorob,this,&MainWindow::heart1);

    connect(ui->action_cutrob,&QAction::triggered,this,[=]()
    {
        ui->checkBox_22->setCheckState(Qt::Unchecked);//未选中
        disconnect(this,&MainWindow::send2,r1,&rob1::rev1);
        disconnect(this,&MainWindow::send3,r1,&rob1::rev2);
        disconnect(this,&MainWindow::send5,r1,&rob1::rev3);
        disconnect(r1,&rob1::send_104,this,&MainWindow::get_104);
        disconnect(r1,&rob1::send_100,this,&MainWindow::get_100);//获取控制字
        disconnect(r1,&rob1::send_102,this,&MainWindow::get_102);//获取控制字
        disconnect(this,&MainWindow::send6,r1,&rob1::rev4);
        disconnect(r1,&rob1::send_,this,&MainWindow::send_position);
        disconnect(this,&MainWindow::send8,r1,&rob1::rev5);
        disconnect(this,&MainWindow::send9,r1,&rob1::rev6);
        disconnect(this,&MainWindow::send10,r1,&rob1::rev7);
        disconnect(this,&MainWindow::send11,r1,&rob1::rev8);
        disconnect(this,&MainWindow::send12,r1,&rob1::rev9);
        disconnect(this,&MainWindow::send13,r1,&rob1::rev10);
        disconnect(r1,&rob1::warning_signal,this,&MainWindow::warning_box);
        disconnect(r1,SIGNAL(flush_modbus_value()),this,SLOT(flushValue()));
        r1->cut4();
    });

    connect(this,&MainWindow::send_plc,p1,&plc::working);
    connect(ui->PLC_action,&QAction::triggered,this,[=]()
    {
        emit send_plc();//发送信号调用机器人工作函数
        t4->start();//子线程启动
    });
    connect(this,&MainWindow::pcl_send4,p1,&plc::rev1);
    connect(p1,&plc::xintiaoplc,this,&MainWindow::heart1);
    //    connect(p1,&plc::xintiao2,this,&MainWindow::heart1);

    connect(ui->action_cutplc,&QAction::triggered,this,[=]()
    {
        ui->checkBox_23->setCheckState(Qt::Unchecked);//未选中
        disconnect(this,&MainWindow::send_plc,p1,&plc::working);
        disconnect(this,&MainWindow::pcl_send4,p1,&plc::rev1);
        disconnect(p1,SIGNAL(flush_modbus_value1()),this,SLOT(flushValue()));
        disconnect(p1,&plc::flush_modbus_value2,this,&MainWindow::pangduan);//获取控制字
        p1->cut();
    });

    //相机基本信息
    property();
    m_log = new LogWidget;
    m_log->show();
    connect(m_log,SIGNAL(login()),this,SLOT(show()));

    connect(r1,&rob1::rob_connected,this,&MainWindow::change_rob);//连接切换头部
    //主窗口背景颜色及字体颜色
    this->setStyleSheet("color:#0bbdc2;background-color:#141626"
                        );
    ui->menuBar->setStyleSheet("QMenu::item:selected{background-color:grey;color:white;}"
                               );
    this->setWindowIcon(QIcon(":/images/icon.png"));
    //表格样式
    ui->property_Widget->setColumnCount(2);
    ui->property_Widget->setRowCount(17);
    ui->property_Widget->setStyleSheet("QTableWidget{background-color: transparent;border: 1px solid white}"
                                       "QTableWidget{gridline-color:white;}"
                                       );
    ui->property_Widget->horizontalHeader()->setVisible(true);
    ui->property_Widget->setHorizontalHeaderLabels(QStringList() << "机器人" << "属性");
    ui->property_Widget->setColumnWidth(0,180);
    ui->property_Widget->setColumnWidth(1,180);
    ui->property_Widget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格内容不可编辑
    //表格2样式
    ui->property_Widget_2->setColumnCount(3);
    ui->property_Widget_2->setRowCount(11);
    ui->property_Widget_2->setStyleSheet("QTableWidget{background-color: transparent;border: 1px solid white}"
                                         "QTableWidget{gridline-color:white;}"
                                         );
    ui->property_Widget_2->horizontalHeader()->setVisible(true);
    //ui->property_Widget_2->setHorizontalHeaderLabels(QStringList() << "机器人" << "属性");
    ui->property_Widget_2->setColumnWidth(0,180);
    ui->property_Widget_2->setColumnWidth(1,90);
    ui->property_Widget_2->setColumnWidth(2,90);
    ui->property_Widget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格内容不可编辑
    //ui->property_Widget->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(42,58,81);border: 1px solid white}");
    //标签样式color: rgb(163, 202, 216);border:1px solid #2b4250
    //    ui->dockWidgetContents_4->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/202.png);}"
    //                                            "QCheckBox::indicator:checked {image: url(:/images/201.png);}"
    //                                            );
    //ui->checkBox_81->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/202.png);}"
    //                                   "QCheckBox::indicator:checked {image: url(:/images/201.png);}");
    ui->checkBox_82->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/202.png);}"
                                   "QCheckBox::indicator:checked {image: url(:/images/201.png);}");
    ui->checkBox_22->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/off.png);}"
                                   "QCheckBox::indicator:checked {image: url(:/images/on.png);}");
    ui->checkBox_23->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/off.png);}"
                                   "QCheckBox::indicator:checked {image: url(:/images/on.png);}");
    //    ui->checkBox_22->setCheckable(false);
    //    ui->checkBox_23->setCheckable(false);
    ui->robot_Dock->setStyleSheet("QCheckBox::indicator:unchecked {image: url(:/images/off.png);}"
                                  "QCheckBox::indicator:checked {image: url(:/images/on.png);}");
    //ui->checkBox_81->setCheckState(Qt::Unchecked);
    ui->checkBox_82->setCheckState(Qt::Checked);
    //ui->checkBox->setCheckState(Qt::Checked);
    //工具栏图标
    ui->home_Action->setIcon(QIcon(":/images/home.png"));
    ui->moniguiji_Actiom->setIcon(QIcon(":/images/road.png"));
    ui->poiling_Action->setIcon(QIcon(":/images/check.png"));
    ui->history_Action->setIcon(QIcon(":/images/list.png"));
    ui->alarm_Action->setIcon(QIcon(":/images/warning.png"));
    //按钮样式
    ui->groupBox_4->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->groupBox_5->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    //演示图样
    //    ui->groupBox->setStyleSheet("border-image: url(:/images/001.jpg);"
    //                                "border: 1px solid white;border-radius:20px");
    //    ui->groupBox_2->setStyleSheet("border-image: url(:/images/002.jpg);"
    //                                  "border: 1px solid white;border-radius:20px");
    //    ui->groupBox_3->setStyleSheet("border-image: url(:/images/002.jpg);"
    //                                  "border: 1px solid white;border-radius:20px");
    //机器人状态面板边框
    ui->dockWidgetContents_15->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                             "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                             "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    //摄像头长宽
    //ui->frame1->height() = ui->frame1->width();
    //更新表格数据
    flushValue();
    //dock栏顺序
    addDockWidget(Qt::LeftDockWidgetArea,ui->dockWidget);
    addDockWidget(Qt::LeftDockWidgetArea,ui->property_Dock);
    addDockWidget(Qt::LeftDockWidgetArea,ui->dockWidget_3);
    addDockWidget(Qt::RightDockWidgetArea,ui->path_Dock);
    //addDockWidget(Qt::RightDockWidgetArea,ui->robot_Dock);
    addDockWidget(Qt::RightDockWidgetArea,ui->dockWidget_2);
    addDockWidget(Qt::RightDockWidgetArea,ui->PLC_dock);
    addDockWidget(Qt::LeftDockWidgetArea,ui->dockWidget_4);
    tabifyDockWidget(ui->dockWidget_2,ui->robot_Dock);
    tabifyDockWidget(ui->PLC_dock,ui->robot_Dock);
    tabifyDockWidget(ui->PLC_dock,ui->dockWidget_2);
    tabifyDockWidget(ui->property_Dock,ui->dockWidget_4);
    //
    newDataBase();

    //    ui->frame1->setUpdatesEnabled(false);
    //    ui->frame2->setsEnabled(false);
    ui->tabWidget_2->setTabText(0,"手动模式配置");
    ui->tabWidget_2->setTabText(1,"自动模式配置");
    ui->tabWidget_2->setTabText(2,"调试模式配置");
    ui->tabWidget_2->setTabText(3,"自由模式配置");
    ui->tabWidget_2->removeTab(3);
    ui->tabWidget_2->setCurrentIndex(0);
    //    ui->tabWidget_2->removeTab(2);

    QStringList strList;
    strList<<"0"<<"0.02"<<"0.04"<<"0.06"<<"0.08"<<"0.1"<<"0.12"<<"0.14"<<"0.16"<<"0.18"<<"0.2";
    ui->comboBox->addItems(strList);

    QRegExp regExp("^(1|[1-9][0-9][0-9]{0,2}|200|2000)$");
    QRegExpValidator *preg_xunjian = new QRegExpValidator(regExp, this);
    ui->lineEdit_2->setValidator(preg_xunjian);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)   //用过滤器eventFilter（）拦截QLabel中的QEvent::Paint事件
{
    if(watched ==ui->label_7 && event->type() == QEvent::Paint)
        Paint();

    return QWidget::eventFilter(watched,event);
}

void MainWindow::Paint()//绘图函数
{
    if(Mp_a==1)
    {
        QPainter painter(ui->label_7);//画笔，this为当前窗口
        Mimage.load(Mfilename);
        QFont font1("Microsoft YaHei", 9);//字体说明
        QFont font2("Microsoft YaHei", 12);
        painter.drawImage(ui->label_7->rect(),QImage(Mimage));
        painter.setFont(font1);
        painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑
        if(Z!=0)
        {
            QSqlQuery sql_query;
            QString str_sql = "";
            QString select_sql1= "select sum(s) from zuobiao";
            QString select_max_sql = "select max(id) from zuobiao";
            if(!sql_query.exec(select_sql1))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    double s = sql_query.value(0).toDouble();
                    MS=s;
                    //qDebug()<<MS;
                }
            }
            if(!sql_query.exec(select_max_sql))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    double l = sql_query.value(0).toDouble();
                    ML=l;
                    //qDebug()<<ML;
                }
            }
            double m,n,y,p;//m为轨迹总长度，n为动态点至起点在图中的轨迹长度
            int x;
            y=0;
            QString str_sql8 = "";
            str_sql8 = QString("select s from zuobiao where rowid = %1").arg(1);
            if(!sql_query.exec(str_sql8))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    double ls = sql_query.value(0).toDouble();
                    guiji_m=ls;
                }
            }
            m =guiji_m;
            //qDebug()<<"m="<<m;
            MS=MS-m;
            //qDebug()<<"MS="<<MS;
            n=(MS*Z)/m;
            for(x=1;x<=ML-1;x++)//不断计算一条线、两条线、三条线的长度，然后比较与n的大小，大于n时说明动态点在x条线内，然后计算点在第x条线的比例
            {
                double Ls;
                str_sql = QString("select s from zuobiao where rowid = %1").arg(x+1);
                if(!sql_query.exec(str_sql))
                {
                    //qDebug()<<sql_query.lastError();
                }
                else
                {
                    while(sql_query.next())
                    {
                        double ls = sql_query.value(0).toDouble();
                        Ls=ls;
                        //qDebug()<<Ls;
                    }
                }
                y=y+Ls;
                if(y>=n)
                {
                    MM=x;
                    //qDebug()<<MM;
                    p=y-Ls;
                    //qDebug()<<p;
                    //qDebug()<<(n-p);
                    //qDebug()<<(y-p);
                    double yxp;//比例
                    yxp=(n-p)/(y-p);
                    //qDebug()<<yxp;
                    MN=(n-p)/(y-p);
                    break;
                }
            }
            painter.setPen(QPen(Qt::green,10));//设置画笔形式
            int A,B,C,D;
            QString str_sql1 = "";
            QString str_sql2 = "";
            QString str_sql3 = "";
            QString str_sql4 = "";
            //qDebug()<<"MM="<<MM;
            str_sql1 = QString("select x from zuobiao where rowid = %1").arg(MM);
            str_sql2 = QString("select x from zuobiao where rowid = %1").arg(MM+1);
            str_sql3 = QString("select y from zuobiao where rowid = %1").arg(MM);
            str_sql4 = QString("select y from zuobiao where rowid = %1").arg(MM+1);
            if(!sql_query.exec(str_sql1))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int a = sql_query.value(0).toDouble();
                    A=a;
                    //qDebug()<<A;
                }
            }
            if(!sql_query.exec(str_sql2))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int c = sql_query.value(0).toDouble();
                    C=c;
                    //qDebug()<<C;
                }
            }
            if(!sql_query.exec(str_sql3))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int b = sql_query.value(0).toDouble();
                    B=b;
                    //qDebug()<<B;
                }
            }
            if(!sql_query.exec(str_sql4))
            {
                //qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int d = sql_query.value(0).toDouble();
                    D=d;
                    //qDebug()<<D;
                }
            }
            painter.drawPoint(0.39*((C-A)*MN+A),0.39*((D-B)*MN+B));
            painter.setPen(QPen(Qt::blue,8));//设置画笔形式
        };
    }
}

void MainWindow::handleTimeout()
{
    Mp_a=1;
    int id;
    QSqlQuery sql_query;
    QString select_max_sql1 = "";
    QString select_max_sql = "select max(id) from student";
    if(!sql_query.exec(select_max_sql))
    {
        //qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            double l = sql_query.value(0).toDouble();
            id=l;
            //qDebug()<<id;
        }
    }
    select_max_sql1 = QString("select xvalue from student where id = %1").arg(id);
    if(!sql_query.exec(select_max_sql1))
    {
        //qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            double s = sql_query.value(0).toDouble();
            Z=s;
            //qDebug()<<"Z="<<Z;
        }
    }
    //qDebug()<<Z;

    ui->frame1->setAttribute(Qt::WA_OpaquePaintEvent);
    ui->frame2->setAttribute(Qt::WA_OpaquePaintEvent);
    update();
}

void MainWindow::property()
{
    ui->property_Widget->setRowCount(17);
    ui->property_Widget->setItem(0,0,new QTableWidgetItem("编码器正转圈数"));
    ui->property_Widget->setItem(1,0,new QTableWidgetItem("编码器反转圈数"));
    ui->property_Widget->setItem(2,0,new QTableWidgetItem("机器人运行总里程"));
    ui->property_Widget->setItem(3,0,new QTableWidgetItem("机器人在轨道上位置"));
    ui->property_Widget->setItem(4,0,new QTableWidgetItem("机器人运行速度"));
    ui->property_Widget->setItem(5,0,new QTableWidgetItem("机器人运行电流"));
    ui->property_Widget->setItem(6,0,new QTableWidgetItem("电池电量"));
    ui->property_Widget->setItem(7,0,new QTableWidgetItem("电池电压"));
    ui->property_Widget->setItem(8,0,new QTableWidgetItem("电池温度"));
    ui->property_Widget->setItem(9,0,new QTableWidgetItem("机器人腔体温度"));
    ui->property_Widget->setItem(10,0,new QTableWidgetItem("CH4浓度值"));
    ui->property_Widget->setItem(11,0,new QTableWidgetItem("O2浓度值"));
    ui->property_Widget->setItem(12,0,new QTableWidgetItem("H2S浓度值"));
    ui->property_Widget->setItem(13,0,new QTableWidgetItem("NH3浓度值"));
    ui->property_Widget->setItem(14,0,new QTableWidgetItem("现场温度"));
    ui->property_Widget->setItem(15,0,new QTableWidgetItem("现场湿度"));
    ui->property_Widget->setItem(16,0,new QTableWidgetItem("自动—已巡检点数"));
    for (int i=0;i<17;i++)
    {
        ui->property_Widget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    ui->property_Widget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(42,58,81);border: 1px solid white}"); //设置表头的背景色
    ui->property_Widget_2->setRowCount(11);
    ui->property_Widget_2->setItem(0,0,new QTableWidgetItem("充电桩充电状态"));
    ui->property_Widget_2->setItem(1,0,new QTableWidgetItem("机器人充电到位信号"));
    ui->property_Widget_2->setItem(2,0,new QTableWidgetItem("电动门开到位"));
    ui->property_Widget_2->setItem(3,0,new QTableWidgetItem("电动门关到位"));
    ui->property_Widget_2->setItem(4,0,new QTableWidgetItem("电动门故障"));
    ui->property_Widget_2->setItem(5,0,new QTableWidgetItem("提升装置上到位"));
    ui->property_Widget_2->setItem(6,0,new QTableWidgetItem("提升装置下到位"));
    ui->property_Widget_2->setItem(7,0,new QTableWidgetItem("提升装置机器人到位1"));
    ui->property_Widget_2->setItem(8,0,new QTableWidgetItem("提升装置机器人到位2"));
    ui->property_Widget_2->setItem(9,0,new QTableWidgetItem("提升装置故障"));
    ui->property_Widget_2->setItem(10,0,new QTableWidgetItem("水池液位高"));
    for (int i=0;i<11;i++)
    {
        ui->property_Widget_2->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    ui->property_Widget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(42,58,81);border: 1px solid white}"); //设置表头的背景色
}

void MainWindow::on_poiling_Action_triggered()
{
    //    if(!ins) {
    ins = new inspection;
    //    }
    ins->show();
    //    connect(ins,&inspection::shoudongxunjian,this,&MainWindow::shoudongxunjian_);
    connect(ins,&inspection::send,this,&MainWindow::rec_ins);
}

void MainWindow::on_history_Action_triggered()
{
    //    if(!his) {
    his = new history;
    //    }
    his->show();
}

void MainWindow::on_alarm_Action_triggered()
{
    warn = new warning;
    warn->show();
}

void MainWindow::on_moniguiji_Actiom_triggered()
{
    moni = new moniguiji;
    moni->show();
    connect(moni,&moniguiji::flush_path,this,&MainWindow::new_path);
    connect(moni,&moniguiji::send,this,&MainWindow::Mrev1);
}

//机器人登录
void MainWindow::on_robot_Action_triggered()
{
    robot_log = new robot_login;
    connect(robot_log,SIGNAL(flush_modbus()),this,SLOT(flushValue()));
    connect(r1,SIGNAL(flush_modbus_value()),this,SLOT(flushValue()));
    //robot_log->show();
    //    if(robot_bool == 0)
    //    {
    //        robot_bool = 2;
    //    }
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox_2->setCheckState(Qt::Unchecked);
    QMessageBox::information(this,"连接中","机器人正在连接，请不要二次点击！");
}

//获取机器人连接状态
void MainWindow::rec_robot_connect_bool(bool a)
{
    if(a==true)
    {
        qDebug()<<"\r\n机器人连接状态：已连接！"<<a;
        if(robot_bool == 0)
        {
            robot_bool = 2;//启动按钮控制
        }
    }
    else
    {
        qDebug()<<"机器人连接状态：已断开连接！！！"<<a;
        robot_bool = 0;//关闭按钮控制
    }
}


//摄像头登录管理界面
void MainWindow::on_add_Action_triggered()
{
    cameraLogin = new camera;
    //connect(cameraLogin,SIGNAL(returnCan2(QString)),this,SLOT(receiveCan(QString)));
    cameraLogin->show();
}

//相机

//更新表格数据
void MainWindow::flushValue(){
    QFile file(file_robot);
    file.open(QIODevice::ReadOnly);
    QDataStream dataStr(&file);

    QString v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17;
    dataStr>> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7 >> v8 >> v9 >> v10 >> v11 >> v12 >> v13 >> v14 >> v15 >> v16 >> v17;
    //qDebug()<<v1<<v2<<v3<<v4<<v5<<v6<<v7<<v8<<v9<<v10<<v11<<v12<<v13<<v14<<v15<<v16<<v17;
    float v3f = QString(v3).toFloat();
    float v4f = QString(v4).toFloat();
    float v5f = QString(v5).toFloat();
    float v6f = QString(v6).toFloat();
    float v8f = QString(v8).toFloat();
    float v9f = QString(v9).toFloat();
    float v10f = QString(v10).toFloat();
    float v11f = QString(v11).toFloat();
    float v12f = QString(v12).toFloat();
    float v13f = QString(v13).toFloat();
    float v14f = QString(v14).toFloat();
    float v15f = QString(v15).toFloat();
    float v16f = QString(v16).toFloat();
    QString v3q =QString("%1").arg(v3f*0.001);
    QString v4q =QString("%1").arg(v4f*0.001);
    QString v5q =QString("%1").arg(v5f*0.01);
    QString v6q =QString("%1").arg(v6f*0.01);
    QString v8q =QString("%1").arg(v8f*0.01);
    QString v9q =QString("%1").arg(v9f*0.01);
    QString v10q =QString("%1").arg(v10f*0.01);
    QString v11q =QString("%1").arg(v11f*0.1);
    QString v12q =QString("%1").arg(v12f*0.1);
    QString v13q =QString("%1").arg(v13f*0.1);
    QString v14q =QString("%1").arg(v14f*0.1);
    QString v15q =QString("%1").arg(v15f*0.1);
    QString v16q =QString("%1").arg(v16f*0.1);
    ui->property_Widget->setItem(0,1,new QTableWidgetItem(v1));
    ui->property_Widget->setItem(1,1,new QTableWidgetItem(v2));
    ui->property_Widget->setItem(2,1,new QTableWidgetItem(v3q));
    ui->property_Widget->setItem(3,1,new QTableWidgetItem(v4q));
    ui->property_Widget->setItem(4,1,new QTableWidgetItem(v5q));
    ui->property_Widget->setItem(5,1,new QTableWidgetItem(v6q));
    ui->property_Widget->setItem(6,1,new QTableWidgetItem(v7));
    ui->property_Widget->setItem(7,1,new QTableWidgetItem(v8q));
    ui->property_Widget->setItem(8,1,new QTableWidgetItem(v9q));
    ui->property_Widget->setItem(9,1,new QTableWidgetItem(v10q));
    ui->property_Widget->setItem(10,1,new QTableWidgetItem(v11q));
    ui->property_Widget->setItem(11,1,new QTableWidgetItem(v12q));
    ui->property_Widget->setItem(12,1,new QTableWidgetItem(v13q));
    ui->property_Widget->setItem(13,1,new QTableWidgetItem(v14q));
    ui->property_Widget->setItem(14,1,new QTableWidgetItem(v15q));
    ui->property_Widget->setItem(15,1,new QTableWidgetItem(v16q));
    ui->property_Widget->setItem(16,1,new QTableWidgetItem(v17));
    file.close();

    QFile file1(file_PLC);
    file1.open(QIODevice::ReadOnly);
    QDataStream dataStr1(&file1);
    QString s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21;
    dataStr1>> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7 >> s8 >> s9 >> s10 >> s11 >> s12 >> s13 >> s14 >> s15 >> s16 >> s17>> s18 >> s19 >> s20 >> s21;
    ui->property_Widget_2->setItem(0,1,new QTableWidgetItem(s1));
    ui->property_Widget_2->setItem(1,1,new QTableWidgetItem(s2));
    ui->property_Widget_2->setItem(2,1,new QTableWidgetItem(s3));
    ui->property_Widget_2->setItem(3,1,new QTableWidgetItem(s4));
    ui->property_Widget_2->setItem(4,1,new QTableWidgetItem(s5));
    ui->property_Widget_2->setItem(5,1,new QTableWidgetItem(s6));
    ui->property_Widget_2->setItem(6,1,new QTableWidgetItem(s7));
    ui->property_Widget_2->setItem(7,1,new QTableWidgetItem(s8));
    ui->property_Widget_2->setItem(8,1,new QTableWidgetItem(s9));
    ui->property_Widget_2->setItem(9,1,new QTableWidgetItem(s10));
    ui->property_Widget_2->setItem(0,2,new QTableWidgetItem(s11));
    ui->property_Widget_2->setItem(1,2,new QTableWidgetItem(s12));
    ui->property_Widget_2->setItem(2,2,new QTableWidgetItem(s13));
    ui->property_Widget_2->setItem(3,2,new QTableWidgetItem(s14));
    ui->property_Widget_2->setItem(4,2,new QTableWidgetItem(s15));
    ui->property_Widget_2->setItem(5,2,new QTableWidgetItem(s16));
    ui->property_Widget_2->setItem(6,2,new QTableWidgetItem(s17));
    ui->property_Widget_2->setItem(7,2,new QTableWidgetItem(s18));
    ui->property_Widget_2->setItem(8,2,new QTableWidgetItem(s19));
    ui->property_Widget_2->setItem(9,2,new QTableWidgetItem(s20));
    ui->property_Widget_2->setItem(10,1,new QTableWidgetItem(s21));
    file1.close();
    //    Sleep(1000);
    //pangduan();
}
//接收子线程相机登录句柄
void MainWindow::rev1(LLONG a)
{
    Login1=a;
}
void MainWindow::rev2(LLONG a)
{
    Login2=a;
}
//选择摄像头
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_2->blockSignals(true);
        ui->checkBox_2->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_2->blockSignals(false);
        Login=Login1;
        //qDebug()<<"Login=Login1="<<Login;
    }
}
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 ==Qt::CheckState::Checked)
    {
        ui->checkBox->blockSignals(true);
        ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox->blockSignals(false);
        Login=Login2;
    }
}
//左上
void MainWindow::on_btn_LUP_clicked()
{
    a=ui->spinBox->value();
    qDebug("a=%d", a);
    LONG lParam1 = a; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_LEFTTOP, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_LEFTTOP, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//上
void MainWindow::on_btn_UP_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_UP_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_UP_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//右上
void MainWindow::on_btn_RUP_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1 = a; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_RIGHTTOP, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_RIGHTTOP, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//左
void MainWindow::on_btn_L_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1 = a; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_LEFT_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_LEFT_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//右
void MainWindow::on_btn_R_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_RIGHT_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_RIGHT_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//左下
void MainWindow::on_btn_LD_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1 = a; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_LEFTDOWN, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_LEFTDOWN, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//下
void MainWindow::on_btn_D_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_DOWN_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_DOWN_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//右下
void MainWindow::on_btn_RD_clicked()
{
    a=ui->spinBox->value();
    //qDebug()<<a;
    LONG lParam1 = a; // 垂直速度
    LONG lParam2 = a; // 水平速度
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_RIGHTDOWN, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_RIGHTDOWN, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}

void MainWindow::on_stop_btn_clicked()
{
    LONG lParam4=0; // 垂直速度
    LONG lParam5=0; // 水平速度
    LONG lParam6=1; //
    BOOL bRet0 = CLIENT_DHPTZControlEx2(Login, 0, DH_EXTPTZ_FASTGOTO, lParam4,
                                        lParam5, lParam6, FALSE, NULL);
}

//变倍-
void MainWindow::on_ZD_btn_clicked()
{
    LONG lParam1; //
    LONG lParam2 = 1; // 倍速
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_ZOOM_DEC_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet1 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_ZOOM_DEC_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//变倍+
void MainWindow::on_ZA_btn_clicked()
{
    LONG lParam1; //
    LONG lParam2 = 1; // 倍速
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_ZOOM_ADD_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet1 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_ZOOM_ADD_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//调焦-
void MainWindow::on_FD_btn_clicked()
{
    LONG lParam1; //
    LONG lParam2 = 1; // 倍速
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_FOCUS_DEC_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet1 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_FOCUS_DEC_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//调焦+
void MainWindow::on_FA_btn_clicked()
{
    LONG lParam1; //
    LONG lParam2 = 1; // 倍速
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_FOCUS_ADD_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet1 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_FOCUS_ADD_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//光圈-
void MainWindow::on_AD_btn_clicked()
{
    LONG lParam1; //
    LONG lParam2 = 1; // 倍速
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_APERTURE_DEC_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet1 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_APERTURE_DEC_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}
//光圈+
void MainWindow::on_AA_btn_clicked()
{
    LONG lParam1; //
    LONG lParam2 = 1; // 倍速
    LONG lParam3; //
    BOOL bRet = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_APERTURE_ADD_CONTROL, lParam1,
                                       lParam2, lParam3, FALSE, NULL);
    Sleep(1000);
    BOOL bRet1 = CLIENT_DHPTZControlEx2(Login, 0, DH_PTZ_APERTURE_ADD_CONTROL, lParam1,
                                        lParam2, lParam3, TRUE, NULL);
}

void MainWindow::on_Ppanel_Action_triggered()
{
    ui->property_Dock->show();
}
void MainWindow::on_Rpanel_Action_triggered()
{
    ui->dockWidget->show();
}
void MainWindow::on_Ppanel_Action_2_triggered()
{
    ui->path_Dock->show();
}

void MainWindow::stopxiancheng()
{
    //    qDebug()<<"表示222222被选中";
    emit send2(Always_switch);
    //    qDebug()<<"表示2222222被选中";
    emit send4();
    //    qDebug()<<"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
}

void MainWindow::startxiancheng()
{
    ui->cam_Action,&QAction::triggered;
    ui->robot_Action,&QAction::triggered;
}

//切换1#机器人
void MainWindow::on_checkBox_82_stateChanged(int arg1)
{
    bool status =ui->checkBox_82->isChecked();
    if(status == true)
    {
        ui->checkBox_81->setCheckState(Qt::Unchecked);
        Always_switch=1;
        stopxiancheng();
    }
    else if(status == false)
    {
    }
    robot_bool = 0;
}

//切换2#机器人
void MainWindow::on_checkBox_81_stateChanged(int arg1)
{
    bool status =ui->checkBox_81->isChecked();
    if(status == true)
    {
        ui->checkBox_82->setCheckState(Qt::Unchecked);
        Always_switch=2;
        stopxiancheng();
    }
    else if(status == false)
    {
    }
    robot_bool = 0;
}

void MainWindow::chufa()
{
    qDebug("我被触发了");
      emit send3(kozhi);
}

void MainWindow::chufa1()
{
    qDebug("我被触发了1");
    emit pcl_send4(plc_kozhi);
}
//送入电机转速
void MainWindow::on_kaiqi_caijiqi_7_clicked()
{
    if(robot_bool == 2){
        speed = (int)ui->comboBox->currentText().toFloat()*10000;
        qDebug()<<"speed"<<speed;
        emit send5(speed);
    }
    else
    {
        //qDebug()<<"robot_bool"<<robot_bool;
    }
}
//停止行进
void MainWindow::on_kaiqi_caijiqi_10_clicked()
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        emit send5(0);
    }
    else
    {
        //qDebug()<<"robot_bool"<<robot_bool;
    }
}

//1#2#电机上电
void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_3->isChecked();
        if(status == true)
        {
            kozhi=1;
            chufa();
        }
        else if(status == false)
        {
            kozhi=2;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_3->setCheckState(Qt::Unchecked);
    }
}


//3#4#电机上电
void MainWindow::on_checkBox_10_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_10->isChecked();
        if(status == true)
        {
            kozhi=3;
            chufa();
        }
        else if(status == false)
        {
            kozhi=4;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_10->setCheckState(Qt::Unchecked);
    }
}
//前摄像头
void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_5->isChecked();
        if(status == true)
        {
            kozhi=9;
            chufa();
        }
        else if(status == false)
        {
            kozhi=10;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_5->setCheckState(Qt::Unchecked);
    }
}
//后摄像头
void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_6->isChecked();
        if(status == true)
        {
            kozhi=11;
            chufa();
        }
        else if(status == false)
        {
            kozhi=12;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_6->setCheckState(Qt::Unchecked);
    }
}
//前灯
void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_7->isChecked();
        if(status == true)
        {
            kozhi=13;
            chufa();
        }
        else if(status == false)
        {
            kozhi=14;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_7->setCheckState(Qt::Unchecked);
    }
}
//后灯
void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_8->isChecked();
        if(status == true)
        {
            kozhi=15;
            chufa();
        }
        else if(status == false)
        {
            kozhi=16;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_8->setCheckState(Qt::Unchecked);
    }
}
//侧灯
void MainWindow::on_checkBox_9_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_9->isChecked();
        if(status == true)
        {
            kozhi=17;
            chufa();
        }
        else if(status == false)
        {
            kozhi=18;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_9->setCheckState(Qt::Unchecked);
    }
}
//电动压杆压紧
void MainWindow::on_checkBox_11_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_11->isChecked();
        if(status == true)
        {
            kozhi=24;
            chufa();
        }
        else if(status == false)
        {
            kozhi=25;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_11->setCheckState(Qt::Unchecked);
    }
}
//电动压杆松开
void MainWindow::on_checkBox_12_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_12->isChecked();
        if(status == true)
        {
            kozhi=26;
            chufa();
        }
        else if(status == false)
        {
            kozhi=27;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_12->setCheckState(Qt::Unchecked);
    }
}
//底摄像头电源
void MainWindow::on_checkBox_13_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_13->isChecked();
        if(status == true)
        {
            kozhi=28;
            chufa();
        }
        else if(status == false)
        {
            kozhi=29;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_13->setCheckState(Qt::Unchecked);
    }
}
//自动-启动
void MainWindow::on_checkBox_14_stateChanged(int arg1)
{
    qDebug()<<"自动-启动开始";
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_14->isChecked();
        if(status == true)
        {
            kozhi=30;
            chufa();
        }
        else if(status == false)
        {
            kozhi=31;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_14->setCheckState(Qt::Unchecked);
    }
    qDebug()<<"自动-启动完成";
}
//一键上电
void MainWindow::on_checkBox_15_stateChanged(int arg1)
{
    qDebug()<<"一键上电开始";
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_15->isChecked();
        // 获取当前选中的复选框个数
        activeCheckboxCount = 0;
        if(ui->checkBox_3->isChecked()==true){
            activeCheckboxCount+=1;//电机12已上电
        }
        if(ui->checkBox_10->isChecked()==true){
            activeCheckboxCount+=2;//电机34已上电
        }
        if(ui->checkBox_5->isChecked()==true){
            activeCheckboxCount+=128;//前摄像头已上电
        }
        if(ui->checkBox_6->isChecked()==true){
            activeCheckboxCount+=256;//后摄像头已上电
        }
        if(status == true)
        {
            emit send_allin(2048+387-activeCheckboxCount);//传入2048+当前与387的差值
        }
        else if(status == false)
        {
            emit send_allin(-2048-activeCheckboxCount);//传入与2048的差值
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_15->setCheckState(Qt::Unchecked);
    }
    qDebug()<<"一键上电完成";
}
//救援机构抬起
void MainWindow::on_checkBox_16_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status = ui->checkBox_16->isChecked();
        if(status == true)
        {
            kozhi=32;
            chufa();
        }
        else if(status == false)
        {
            kozhi=33;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_16->setCheckState(Qt::Unchecked);
    }
}
//救援机构落下
void MainWindow::on_checkBox_18_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_18->isChecked();
        if(status == true)
        {
            kozhi=34;
            chufa();
        }
        else if(status == false)
        {
            kozhi=35;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_18->setCheckState(Qt::Unchecked);
    }
}
//1#继电器
void MainWindow::on_checkBox_19_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_19->isChecked();
        if(status == true)
        {
            kozhi=36;
            chufa();
        }
        else if(status == false)
        {
            kozhi=37;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_19->setCheckState(Qt::Unchecked);
    }
}
//2#继电器
void MainWindow::on_checkBox_20_stateChanged(int arg1)
{
    if(robot_bool == 2){
        //qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_20->isChecked();
        if(status == true)
        {
            kozhi=38;
            chufa();
        }
        else if(status == false)
        {
            kozhi=39;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_20->setCheckState(Qt::Unchecked);
    }
}


//机器人行进方向
void MainWindow::on_checkBox_17_stateChanged(int arg1)
{
    if(robot_bool == 2){
        ////qDebug()<<"robot_bool"<<robot_bool;
        bool status =ui->checkBox_17->isChecked();
        if(status == true)
        {
            kozhi=20;
            chufa();
        }
        else if(status == false)
        {
            kozhi=21;
            chufa();
        }
    }
    else if(robot_bool == 1){
        //qDebug()<<"robot_bool"<<robot_bool;
    }
    else if(robot_bool == 0)
    {
        //qDebug()<<"robot_bool"<<robot_bool;
        ui->checkBox_17->setCheckState(Qt::Unchecked);
    }
}

//全体断电
void MainWindow::on_kaiqi_caijiqi_8_clicked()
{
    if(robot_bool == 2){
        robot_bool = 1;
        //qDebug()<<"robot_bool"<<robot_bool;
        kozhi=19;
        chufa();
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->checkBox_5->setCheckState(Qt::Unchecked);
        ui->checkBox_6->setCheckState(Qt::Unchecked);
        ui->checkBox_7->setCheckState(Qt::Unchecked);
        ui->checkBox_8->setCheckState(Qt::Unchecked);
        ui->checkBox_9->setCheckState(Qt::Unchecked);
        ui->checkBox_10->setCheckState(Qt::Unchecked);
        ui->checkBox_11->setCheckState(Qt::Unchecked);
        ui->checkBox_12->setCheckState(Qt::Unchecked);
        ui->checkBox_13->setCheckState(Qt::Unchecked);
        ui->checkBox_14->setCheckState(Qt::Unchecked);
        ui->checkBox_15->setCheckState(Qt::Unchecked);
        ui->checkBox_16->setCheckState(Qt::Unchecked);
        ui->checkBox_18->setCheckState(Qt::Unchecked);
        ui->checkBox_19->setCheckState(Qt::Unchecked);
        ui->checkBox_20->setCheckState(Qt::Unchecked);
        robot_bool = 2;
    }
    else
    {
        //qDebug()<<"robot_bool"<<robot_bool;
    }
}
//获取控制字
void MainWindow::get_104(int a)
{
    robot_104=a;
    qDebug()<<"MainWindow获取控制字104："<<robot_104;
    calculation();
}
void MainWindow::get_100(int a)
{
    float robot_100 =(float)a*0.0001;
    if(robot_bool == 2){
        robot_bool = 1;
        QString speed100 = "当前电机速度："+QString::number(robot_100)+"m/s";
        ui->label_5->setText(speed100);
        robot_bool = 2;
    }
}
void MainWindow::get_102(int a)
{
    int robot_102 = a;
    if(robot_bool == 2){
        robot_bool = 1;
        if(robot_102==0){
            ui->checkBox_17->setCheckState(Qt::Unchecked);
        }
        if(robot_102==1){
            ui->checkBox_17->setCheckState(Qt::Checked);
        }
        robot_bool = 2;
    }
}
void MainWindow::calculation()//根据控制字判断
{
    qDebug()<<"robot_bool:"<<robot_bool;
    if(robot_bool == 2){
        robot_bool = 1;
        if(robot_104>=32768)
        {
            ui->checkBox_20->setCheckState(Qt::Checked);
            robot_104-=32768;
            //qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_20->setCheckState(Qt::Unchecked);
        }

        Sleep(50);
        if(robot_104>=16384)
        {
            ui->checkBox_19->setCheckState(Qt::Checked);
            robot_104-=16384;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_19->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=8192)
        {
            ui->checkBox_18->setCheckState(Qt::Checked);
            robot_104-=8192;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_18->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=4096)
        {
            ui->checkBox_16->setCheckState(Qt::Checked);
            robot_104-=4096;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_16->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=2048)
        {
            ui->checkBox_15->setCheckState(Qt::Checked);
            robot_104-=2048;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_15->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=1024)
        {
            ui->checkBox_14->setCheckState(Qt::Checked);
            robot_104-=1024;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_14->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=512)
        {
            ui->checkBox_13->setCheckState(Qt::Checked);
            robot_104-=512;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_13->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=256)
        {
            ui->checkBox_6->setCheckState(Qt::Checked);
            robot_104-=256;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_6->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=128)
        {
            ui->checkBox_5->setCheckState(Qt::Checked);
            robot_104-=128;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_5->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=64)
        {
            ui->checkBox_9->setCheckState(Qt::Checked);
            robot_104-=64;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_9->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=32)
        {
            ui->checkBox_8->setCheckState(Qt::Checked);
            robot_104-=32;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_8->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=16)
        {
            ui->checkBox_7->setCheckState(Qt::Checked);
            robot_104-=16;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_7->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=8)
        {
            ui->checkBox_12->setCheckState(Qt::Checked);
            robot_104-=8;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_12->setCheckState(Qt::Unchecked);
        }
        Sleep(100);
        if(robot_104>=4)
        {
            ui->checkBox_11->setCheckState(Qt::Checked);
            robot_104-=4;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_11->setCheckState(Qt::Unchecked);
        }
        Sleep(50);
        if(robot_104>=2)
        {
            ui->checkBox_10->setCheckState(Qt::Checked);
            robot_104-=2;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_10->setCheckState(Qt::Unchecked);
        }

        if(robot_104>=1)
        {
            ui->checkBox_3->setCheckState(Qt::Checked);
            robot_104-=1;
            ////qDebug()<<"MainWindow  robot_104:"<<robot_104;
        }
        else
        {
            ui->checkBox_3->setCheckState(Qt::Unchecked);
        }
        robot_bool = 2;//进入状态二，可以进行控制
    }
}
void MainWindow::send_position(int data)
{
    //    qDebug()<<"send_position"<<data<<xunjian_count;
    if(xunjian_points.size()==0)
    {
        xunjian_points.push_back(data);
        //qDebug()<<xunjian_points;
    }
    //    else
    //    {
    //        xunjian_points.push_back(data);
    //        if(xunjian_count == xunjian_stringlist.length()-1 && xunjian_points[1] == xunjian_stringlist[xunjian_stringlist.length()-1].split(" ")[1].toInt()){
    //            disconnect(r1,&rob1::send,this,&MainWindow::send_position);
    //            xunjian_points.clear();
    //        }
    //        else if ((xunjian_points[0]-xunjian_stringlist[xunjian_count].split(" ")[1].toInt())*(xunjian_points[1]-xunjian_stringlist[xunjian_count].split(" ")[1].toInt())<=0 && xunjian_count == xunjian_stringlist.length()-1)
    //        {
    //            disconnect(r1,&rob1::send,this,&MainWindow::send_position);
    //            xunjian_points.clear();
    //        }
    //        else if ((xunjian_points[0]-xunjian_stringlist[xunjian_count].split(" ")[1].toInt())*(xunjian_points[1]-xunjian_stringlist[xunjian_count].split(" ")[1].toInt())<=0) {
    //            xunjian_count+=1;
    //            quick_positiving(xunjian_stringlist,xunjian_count);
    //            //qDebug()<<xunjian_stringlist[xunjian_count];
    //            if(xunjian_count >= xunjian_stringlist.length()){
    //                disconnect(r1,&rob1::send,this,&MainWindow::send_position);
    //                xunjian_points.clear();
    //            }
    //        }
    //        if(!xunjian_points.empty()){
    //            xunjian_points.remove(0);
    //        }
    //    }
    xunjian_points.push_back(data);
    int length = xunjian_stringlist.length()-1;
    int xunjiandian = xunjian_stringlist[length].split(" ")[1].toInt();
    int xunjiandian_1 = xunjian_stringlist[xunjian_count].split(" ")[1].toInt();
    //qDebug()<<xunjian_count<<xunjiandian_1<<length<<"xunjiandian"<<xunjian_points[0]<<xunjian_points[1];
    //qDebug()<<(xunjian_points[0]-xunjiandian_1)*(xunjian_points[1]-xunjiandian_1);
    if(xunjian_count == length && xunjian_points[1] == xunjiandian){
        quick_positiving(xunjian_stringlist,xunjian_count);
        xunjian_points.clear();
        xunjian_count = 0;
        disconnect(r1,&rob1::send_,this,&MainWindow::send_position);
        ui->checkBox_14->setCheckState(Qt::Unchecked);
        return;
    }
    if(xunjian_count == length && (xunjian_points[0]-xunjiandian)*(xunjian_points[1]-xunjiandian)<=0 )
    {
        quick_positiving(xunjian_stringlist,xunjian_count);
        xunjian_points.clear();
        xunjian_count = 0;
        disconnect(r1,&rob1::send_,this,&MainWindow::send_position);
        ui->checkBox_14->setCheckState(Qt::Unchecked);
        return;
    }
    if(xunjian_count>length){
        xunjian_points.clear();
        xunjian_count = 0;
        disconnect(r1,&rob1::send_,this,&MainWindow::send_position);
        ui->checkBox_14->setCheckState(Qt::Unchecked);
        return;
    }
    if(xunjian_count <= length && (xunjian_points[0]-xunjiandian_1)*(xunjian_points[1]-xunjiandian_1)<=0)
    {
        qDebug()<<"send_position"<<xunjian_points<<xunjiandian_1<<xunjian_count;
        quick_positiving(xunjian_stringlist,xunjian_count);
        xunjian_count+=1;
        ui->lineEdit_15->setText(QString("%1/%2").arg(xunjian_count).arg(xunjian_stringlist.length()));
        xunjian_points.remove(0);
        return;
    }
    if(xunjian_count <= length && xunjian_points[0] == xunjiandian_1 && xunjian_points[1] == xunjiandian_1)
    {
        quick_positiving(xunjian_stringlist,xunjian_count);
        xunjian_count+=1;
        ui->lineEdit_15->setText(QString("%1/%2").arg(xunjian_count).arg(xunjian_stringlist.length()));
        xunjian_points.remove(0);
        return;
    }
    xunjian_points.remove(0);
}

//void MainWindow::on_pushButton_6_clicked()
//{
//    xunjian_points.clear();
//    disconnect(r1,&rob1::send_,this,&MainWindow::send_position);
//    ui->checkBox_14->setCheckState(Qt::Unchecked);
//}

//void MainWindow::shoudongxunjian_(QStringList data)
//{
//    Sleep(500);
//    //qDebug()<<data;
//    quick_positiving(data,0);
//    emit send8(data[0].split(" ")[1].toInt());
//}
void MainWindow::quick_positiving(QStringList stringlist,int count)
{
    LONG lParam1 = stringlist[count].split(" ")[2].toInt()*10;
    LONG lParam2 = stringlist[count].split(" ")[3].toInt()*10;
    LONG lParam3;
    LONG lParam11 = stringlist[count].split(" ")[4].toInt()*10;
    LONG lParam22 = stringlist[count].split(" ")[5].toInt()*10;
    LONG lParam33;
    //qDebug()<<"摄像头参数"<<lParam1<<lParam2<<lParam11<<lParam22;
    //qDebug()<<lParam1<<lParam1<<lParam11<<lParam22;
    //qDebug()<<Login<<Login1<<Login2;
    if(Login == Login1){
        BOOL bRet = CLIENT_DHPTZControlEx2(Login1,0,DH_EXTPTZ_EXACTGOTO,lParam1,lParam2,lParam3, FALSE, NULL);
        Sleep(1000);
        BOOL bRet1 = CLIENT_DHPTZControlEx2(Login1,0,DH_EXTPTZ_EXACTGOTO,lParam1,lParam2,lParam3, TRUE, NULL);
        if(Login2 && Login2!=Login1)
        {
            BOOL bRet_1 = CLIENT_DHPTZControlEx2(Login2,0,DH_EXTPTZ_EXACTGOTO,lParam11,lParam22,lParam33, FALSE, NULL);
            Sleep(1000);
            BOOL bRet_2 = CLIENT_DHPTZControlEx2(Login2,0,DH_EXTPTZ_EXACTGOTO,lParam11,lParam22,lParam33, TRUE, NULL);
        }
    }
    else if(Login == Login2)
    {
        BOOL bRet_1 = CLIENT_DHPTZControlEx2(Login2,0,DH_EXTPTZ_EXACTGOTO,lParam11,lParam22,lParam33, FALSE, NULL);
        Sleep(1000);
        BOOL bRet_2 = CLIENT_DHPTZControlEx2(Login2,0,DH_EXTPTZ_EXACTGOTO,lParam11,lParam22,lParam33, TRUE, NULL);
        if(Login1 && Login1!=Login2)
        {
            BOOL bRet = CLIENT_DHPTZControlEx2(Login1,0,DH_EXTPTZ_EXACTGOTO,lParam1,lParam2,lParam3, FALSE, NULL);
            Sleep(1000);
            BOOL bRet1 = CLIENT_DHPTZControlEx2(Login1,0,DH_EXTPTZ_EXACTGOTO,lParam1,lParam2,lParam3, TRUE, NULL);
        }
    }
}
//更新路径图片
void MainWindow::new_path()
{
    m_timer.setInterval(1000);
    m_timer.start();
    //qDebug()<<"我是定时器启动";
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    ui->label_7->setStyleSheet("border-image: url(./path.jpg)");
    //qDebug()<<"更新路径图";
}
////视频录制
//void MainWindow::on_pushButton_3_clicked()
//{
//    qDebug("开始录制");
//}

////停止录制
//void MainWindow::on_pushButton_4_clicked()
//{

//}
//创建数据库并连接
void MainWindow::newDataBase()
{
    //创建数据库并连接
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("HeFanRobot");
        database.setPassword("123456");
    }
    //判断数据库连接
    if (!database.open())
    {
        //qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        //qDebug()<<"DataBase open sucess!";
    }
    //创建student表
    QSqlQuery sql_query;

    QString str_sql = "";

    str_sql = "create table student (id int primary key,time1 text,time2 text unique,"
              "speed double,BatteryVoltage double,RobotTemperature double,"
              "CH4Value double,O2Value double,H2SValue double,NH3Value double,"
              "Temperature double,Humidity double,xvalue double)";
    if(!sql_query.exec(str_sql))
    {
        //qDebug()<<"创建student表失败！！"<< sql_query.lastError();
    }
    else
    {
        //qDebug()<<"创建student表成功";

    }

    //创建warningValue表
    str_sql = "create table warningValue (id int primary key,time1 text,time2 text,"
              "speed1 double,speed2 double,"
              "BatteryVoltage1 double,BatteryVoltage2 double,"
              "RobotTemperature1 double,RobotTemperature2 double,"
              "CH4Value1 double,CH4Value2 double,"
              "O2Value1 double,O2Value2 double,"
              "H2SValue1 double,H2SValue2 double,"
              "NH3Value1 double,NH3Value2 double,"
              "Temperature1 double,Temperature2 double,"
              "Humidity1 double,Humidity2 double)";
    if(!sql_query.exec(str_sql))
    {
        //qDebug()<<"创建warningValue表失败！！"<< sql_query.lastError();
    }
    else
    {
        //qDebug()<<"创建warningValue表成功";

    }

    //创建warning表
    str_sql = "create table warning (id int primary key,time1 text,time2 text,"
              "speed double,BatteryVoltage double,RobotTemperature double,"
              "CH4Value double,O2Value double,H2SValue double,NH3Value double,"
              "Temperature double,Humidity double,xvalue double)";
    if(!sql_query.exec(str_sql))
    {
        //qDebug()<<"创建warning表失败！！"<< sql_query.lastError();
    }
    else
    {
        //qDebug()<<"创建warning表成功";

    }
}

//报警弹窗
void MainWindow::warning_box(int a)
{
    if(a==1){
        ui->label_9->setText("警告,存在数值超出预警值！");
    }
    if(a==0){
        ui->label_9->setText("数值无异常");
    }
}

void MainWindow::Mrev1(int a)
{
    guiji_m=a;
}

void MainWindow::on_actionkong_triggered()
{
    ui->dockWidget_2->show();
}

void MainWindow::on_actionjiqiren_triggered()
{
    ui->robot_Dock->show();
}


void MainWindow::on_cam_Action_triggered()
{
    QMessageBox::information(this,"连接中","摄像头正在连接");
}


void MainWindow::on_pushButton_5_clicked()
{
    //    ui->checkBox_14->setCheckState(Qt::Unchecked);
    int count_putton = 0;
    if(ui->checkBox_32->isChecked()){
        count_putton += 1;
    }
    if(ui->checkBox_34->isChecked()){
        count_putton += 1;
    }
    if(ui->checkBox_33->isChecked()){
        count_putton += 1;
    }
    if(ui->checkBox_35->isChecked()){
        count_putton += 1;
    }

    if(!count_putton == 1){
        QMessageBox::warning(this,"提示","检查勾选框",QMessageBox::Ok);
        return;
    }
    if(ui->checkBox_34->isChecked())//自动巡检
    {
        //        if(!ui->checkBox_3->isChecked()){
        //            ui->checkBox_3->setCheckState(Qt::Checked);
        //        }
        //        Sleep(50);
        //        if(!ui->checkBox_10->isChecked()){
        //            ui->checkBox_10->setCheckState(Qt::Checked);
        //        }
        //        Sleep(50);
        ui->tabWidget_2->setCurrentIndex(1);
        QString xunjianpath_0;
        //        if(!ui->checkBox_5->isChecked()){
        //            ui->checkBox_5->setCheckState(Qt::Checked);
        //        }
        //        if(!ui->checkBox_6->isChecked()){
        //            ui->checkBox_6->setCheckState(Qt::Checked);
        //        }
        if(xunjianpath != "")
        {
            xunjianpath_0 = QFileDialog::getOpenFileName(this,"打开",xunjianpath);
        }
        else {
            xunjianpath_0 = QFileDialog::getOpenFileName(this,"打开","../");
        }
        QString string;
        xunjian_stringlist.clear();
        xunjian_count=0;
        if (xunjianpath_0.isEmpty() == false){
            QFile file(xunjianpath_0);
            bool isok = file.open(QIODevice::ReadOnly);
            if (isok){
                while(file.atEnd() == false){
                    string = file.readLine();
                    string.remove("\r\n");
                    //qDebug()<<string;
                    xunjian_stringlist.append(string);
                }
            }
            for (int i = 0; i<xunjian_stringlist.length(); i++) {
                emit send6(xunjian_stringlist[i].split(" ")[1].toInt(),i);
                if(i==0){
                    Sleep(500);
                    QString string_temp =ui->lineEdit_16->text();
                    if(string_temp == ""){
                        QMessageBox::information(this,"提示","请检查表格内容");
                        return;
                    }
                    else
                    {
                        emit send11(string_temp.toInt());//传递自动巡检速度参数
                    }
                }
                Sleep(100);
            }
            Sleep(100);
            emit send9(xunjian_stringlist.length());
            Sleep(100);
            //qDebug()<<"ok";
            emit send7();
            quick_positiving(xunjian_stringlist,xunjian_count);
            if(ui->checkBox_38->isChecked()){
                emit send10(0);
            }else if (ui->checkBox_39->isChecked()) {
                emit send10(1);
            }
            Sleep(100);
            //传递开启信号
            emit send12(ui->lineEdit_14->text().toInt());
            ui->lineEdit_15->setText(QString("%1/%2").arg(0).arg(xunjian_stringlist.length()));
            Sleep(100);
            emit send13(2);
            ui->statusBar->showMessage(tr("机器人处于自动模式"));
            Sleep(100);
            ui->checkBox_14->setCheckState(Qt::Checked);
            Sleep(100);
        }
    }
    if(ui->checkBox_32->isChecked())//手动模式
    {
        if(ui->checkBox_37->isChecked() && ui->checkBox_36->isChecked()){
            QMessageBox::information(this,"提示","请设置机器人运行方向");
            return;
        }
        if(!ui->checkBox_37->isChecked() && !ui->checkBox_36->isChecked()){
            QMessageBox::information(this,"提示","请设置机器人运行方向");
            return;
        }
        if(ui->checkBox_36->isChecked()){
            ui->checkBox_17->setCheckState(Qt::Unchecked);
        }
        Sleep(100);
        if(ui->checkBox_37->isChecked()){
            ui->checkBox_17->setCheckState(Qt::Checked);
        }
        Sleep(100);
        //        ui->tabWidget_2->setCurrentIndex(0);
        //        if(!ui->checkBox_3->isChecked()){
        //            ui->checkBox_3->setCheckState(Qt::Checked);
        //        }
        //        Sleep(50);
        //        if(!ui->checkBox_10->isChecked()){
        //            ui->checkBox_10->setCheckState(Qt::Checked);
        //        }
        //        Sleep(50);
        //        if(!ui->checkBox_5->isChecked()){
        //            //qDebug()<<"前摄像头未打开";
        //            ui->checkBox_5->setCheckState(Qt::Checked);
        //        }
        //        Sleep(50);
        //        if(!ui->checkBox_6->isChecked()){
        //            //qDebug()<<"前摄像头未打开";
        //            ui->checkBox_6->setCheckState(Qt::Checked);
        //        }
        Sleep(100);
        if(ui->lineEdit_13->text() != ""){
            float weizhi;
            weizhi=(int)(ui->lineEdit_13->text().toFloat()*1000);
            qDebug()<<"待输入位置"<<weizhi;
            emit send8(weizhi);
            Sleep(100);
            QString string_temp1 =ui->lineEdit_12->text();
            //qDebug()<<"待输入速度"<<string_temp1;
            Sleep(100);
            emit send13(1);
            if(string_temp1==""){
                QMessageBox::information(this,"提示","请输入速度");//默认速度，在主窗口更改
            }
            else{
                int data_temp = string_temp1.toFloat()*10000;
                qDebug()<<"速度shi"<<typeid (data_temp).name()<<data_temp;
                emit send5(data_temp);
            }
            Sleep(100);
            //            if(!ui->checkBox_14->isChecked()){
            //                ui->checkBox_14->setCheckState(Qt::Checked);
            //            }
            ui->statusBar->showMessage(tr("机器人处于手动模式"));
            Sleep(100);
            return;
        }
    }
    if(ui->checkBox_35->isChecked())//调试模式
    {
        ui->tabWidget_2->setCurrentIndex(2);
        if(ui->lineEdit_2->text()==""){
            emit send8(ui->lineEdit_2->text().toFloat());
        }
        Sleep(100);
        emit send13(0);
        ui->statusBar->showMessage(tr("机器人处于调试模式"));
        qDebug()<<"调试任务启动完成";
        return;
    }
    if(ui->checkBox_33->isChecked())//自由模式
    {
        //        ui->tabWidget_2->setCurrentIndex(3);
        emit send13(3);
        ui->statusBar->showMessage(tr("机器人处于自由模式"));
        return;
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(ui->checkBox_34->isChecked()){
        xunjian_points.clear();
        disconnect(r1,&rob1::send_,this,&MainWindow::send_position);
        Sleep(100);
        if(xunjian_count+1 <= xunjian_stringlist.length()){
            emit send9(xunjian_count+1);
        }
        Sleep(100);
        ui->checkBox_14->setCheckState(Qt::Unchecked);
        ui->lineEdit_15->setText(QString("%1/%2").arg(xunjian_count).arg(xunjian_count+1));
    }
    if(ui->checkBox_32->isChecked()){
        if(ui->checkBox_14->isChecked()){
            ui->checkBox_14->setCheckState(Qt::Unchecked);
        }
        emit send5(0);
    }
}

void MainWindow::on_checkBox_32_stateChanged(int arg1)
{
    if(ui->checkBox_32->isChecked()){
        ui->checkBox_33->setCheckState(Qt::Unchecked);
        ui->checkBox_34->setCheckState(Qt::Unchecked);
        ui->checkBox_35->setCheckState(Qt::Unchecked);
        ui->tabWidget_2->setCurrentIndex(0);
    }
}

void MainWindow::on_checkBox_34_stateChanged(int arg1)
{
    if(ui->checkBox_34->isChecked()){
        ui->checkBox_33->setCheckState(Qt::Unchecked);
        ui->checkBox_32->setCheckState(Qt::Unchecked);
        ui->checkBox_35->setCheckState(Qt::Unchecked);
        ui->tabWidget_2->setCurrentIndex(1);
    }
}

void MainWindow::on_checkBox_35_stateChanged(int arg1)
{
    if(ui->checkBox_35->isChecked()){
        ui->checkBox_33->setCheckState(Qt::Unchecked);
        ui->checkBox_32->setCheckState(Qt::Unchecked);
        ui->checkBox_34->setCheckState(Qt::Unchecked);
        ui->tabWidget_2->setCurrentIndex(2);
    }
}

void MainWindow::on_checkBox_33_stateChanged(int arg1)
{
    if(ui->checkBox_33->isChecked()){
        ui->checkBox_34->setCheckState(Qt::Unchecked);
        ui->checkBox_32->setCheckState(Qt::Unchecked);
        ui->checkBox_35->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_36_stateChanged(int arg1)
{
    if(ui->checkBox_36->isChecked()){
        ui->checkBox_37->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_37_stateChanged(int arg1)
{
    if(ui->checkBox_37->isChecked()){
        ui->checkBox_36->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_39_stateChanged(int arg1)
{
    if(ui->checkBox_39->isChecked()){
        ui->checkBox_38->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_38_stateChanged(int arg1)
{
    if(ui->checkBox_38->isChecked()){
        ui->checkBox_39->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::change_rob(int a)
{
    qDebug()<<"----------------------------------------aaaa"<<a;
    //    if(a==1){
    //        qDebug()<<"----------------------------------------1111";
    //        ui->checkBox_82->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/203.png);}");//选中已连接
    //        ui->checkBox_81->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/202.png);}");//未选中
    //    }
    //    if(a==2){
    //        qDebug()<<"----------------------------------------2222";
    //        ui->checkBox_81->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/203.png);}");//选中已连接
    //        ui->checkBox_82->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/202.png);}");//未选中
    //    }
    //    if(a==3){
    //        qDebug()<<"----------------------------------------3333";
    //        ui->checkBox_81->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/202.png);}");//未选中
    //        ui->checkBox_82->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/201.png);}");//选中未连接
    //    }
    //    if(a==4){
    //        qDebug()<<"----------------------------------------4444";
    //        ui->checkBox_81->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/201.png);}");//选中未连接
    //        ui->checkBox_82->setStyleSheet("QCheckBox::indicator:checked {image: url(:/images/202.png);}");//未选中
    //    }

}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(ui->checkBox_4->isChecked()){
        ui->checkBox_15->setCheckState(Qt::Checked);
    }
    if(!ui->checkBox_4->isChecked()){
        ui->checkBox_15->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_41_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_41->isChecked();
        if(status == true)
        {
            plc_kozhi=1;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=2;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_41->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_25_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_25->isChecked();
        if(status == true)
        {
            plc_kozhi=3;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=4;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_25->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_24_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_24->isChecked();
        if(status == true)
        {
            plc_kozhi=5;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=6;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_24->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_27_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_27->isChecked();
        if(status == true)
        {
            plc_kozhi=7;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=8;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_27->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_28_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_28->isChecked();
        if(status == true)
        {
            plc_kozhi=9;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=10;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_28->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_29_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_29->isChecked();
        if(status == true)
        {
            plc_kozhi=11;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=12;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_29->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_42_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_42->isChecked();
        if(status == true)
        {
            plc_kozhi=13;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=14;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_42->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_31_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_31->isChecked();
        if(status == true)
        {
            plc_kozhi=15;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=16;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_31->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_30_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_30->isChecked();
        if(status == true)
        {
            plc_kozhi=17;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=18;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_30->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_21_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_21->isChecked();
        if(status == true)
        {
            plc_kozhi=19;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=20;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_21->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_26_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_26->isChecked();
        if(status == true)
        {
            plc_kozhi=21;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=22;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_26->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_44_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_44->isChecked();
        if(status == true)
        {
            plc_kozhi=23;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=24;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_44->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_40_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_40->isChecked();
        if(status == true)
        {
            plc_kozhi=25;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=26;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_40->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_checkBox_43_stateChanged(int arg1)
{
    if(plc_bool == 1){
        bool status =ui->checkBox_43->isChecked();
        if(status == true)
        {
            plc_kozhi=27;
            chufa1();
        }
        else if(status == false)
        {
            plc_kozhi=28;
            chufa1();
        }
    }
    else if(plc_bool == 0)
    {
        ui->checkBox_43->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_PLC_action_triggered()
{
    connect(p1,SIGNAL(flush_modbus_value1()),this,SLOT(flushValue()));
    connect(p1,&plc::flush_modbus_value2,this,&MainWindow::pangduan);//获取控制字
    if(plc_bool == 0)
    {
        plc_bool = 2;
    }
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox_2->setCheckState(Qt::Unchecked);
    QMessageBox::information(this,"连接中","plc正在连接，请不要二次点击！");
}

void MainWindow::pangduan()
{
    QFile file2(file_PLC2);
    file2.open(QIODevice::ReadOnly);
    QDataStream dataStr2(&file2);
    QString s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31,s32,s33,s34,s35,s36;
    dataStr2>> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7 >> s8 >> s9 >> s10 >> s11 >> s12 >> s13 >> s14 >> s15 >> s16 >> s17>> s18 >> s19 >> s20 >> s21 >> s22 >> s23 >> s24 >> s25 >> s26 >> s27 >> s28 >> s29 >> s30 >> s31 >> s32 >> s33 >> s34 >> s35 >> s36;
    qDebug()<<"s22"<<s22;
    qDebug()<<"s36="<<s36;
    int ss22=s22.toInt();
    int ss23=s23.toInt();
    int ss24=s24.toInt();
    int ss25=s25.toInt();
    int ss26=s26.toInt();
    int ss27=s27.toInt();
    int ss28=s28.toInt();
    int ss30=s30.toInt();
    int ss31=s31.toInt();
    int ss32=s32.toInt();
    int ss33=s33.toInt();
    int ss34=s34.toInt();
    int ss35=s35.toInt();
    int ss36=s36.toInt();
    if(ss22==1)
    {
        ui->checkBox_41->setCheckState(Qt::Checked);
        qDebug()<<"s22on="<<s22;
    }
    else
    {
        ui->checkBox_41->setCheckState(Qt::Unchecked);
        qDebug()<<"s22off"<<s22;
    }
    if(ss23==1)
    {
        ui->checkBox_25->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_25->setCheckState(Qt::Unchecked);
    }
    if(ss24==1)
    {
        ui->checkBox_24->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_24->setCheckState(Qt::Unchecked);
    }
    if(ss25==1)
    {
        ui->checkBox_27->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_27->setCheckState(Qt::Unchecked);
    }
    if(ss26==1)
    {
        ui->checkBox_28->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_28->setCheckState(Qt::Unchecked);
    }
    if(ss27==1)
    {
        ui->checkBox_29->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_29->setCheckState(Qt::Unchecked);
    }
    if(ss28==1)
    {
        ui->checkBox_42->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_42->setCheckState(Qt::Unchecked);
    }
    if(ss30==1)
    {
        ui->checkBox_31->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_31->setCheckState(Qt::Unchecked);
    }
    if(ss31==1)
    {
        ui->checkBox_30->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_30->setCheckState(Qt::Unchecked);
    }
    if(ss32==1)
    {
        ui->checkBox_21->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_21->setCheckState(Qt::Unchecked);
    }
    if(ss33==1)
    {
        ui->checkBox_26->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_26->setCheckState(Qt::Unchecked);
    }
    if(ss34==1)
    {
        ui->checkBox_44->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_44->setCheckState(Qt::Unchecked);
    }
    if(ss35==1)
    {
        ui->checkBox_40->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_40->setCheckState(Qt::Unchecked);
    }
    if(ss36==1)
    {
        ui->checkBox_43->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_43->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::heart1(int a)
{
    heartbeat=a;
    if(heartbeat==2)
    {
        ui->checkBox_23->setCheckState(Qt::Checked);//未选中
        disconnect(p1,&plc::xintiaoplc,this,&MainWindow::heart1);
    }
    if(heartbeat==1)
    {
        qDebug()<<"s22";
        ui->checkBox_22->setCheckState(Qt::Checked);//选中未连接
        disconnect(r1,&rob1::xintiaorob,this,&MainWindow::heart1);
    }
}
