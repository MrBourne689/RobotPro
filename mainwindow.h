#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "logwidget.h"
#include <QMainWindow>
#include "inspection.h"
#include "history.h"
#include "warning.h"
#include "moniguiji.h"
#include "xiancheng.h"
#include <QThread>
//机器人登录
#include "robot_login.h"
//相机
#include "avglobal.h"
#include "dhconfigsdk.h"
#include "dhnetsdk.h"
//相机登录管理界面
#include "camera.h"
#include "camera_login.h"
#include <QMetaType>

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
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

#define IP1 "192.168.2.109"
#define PORT1 "37777"
#define USER1 "admin"
#define PASSWD1 "admin123"
#define IP2 "192.168.2.105"
#define PORT2 "37777"
#define USER2 "admin"
#define PASSWD2 "admin123"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void property();

    static QString robot1_IP;
    static QString robot1_PORT;
    static QString robot1_USERNAME;
    static QString robot1_PASSWORD;
    static QString robot2_IP;
    static QString robot2_PORT;
    static QString robot2_USERNAME;
    static QString robot2_PASSWORD;

    static int robot_bool;//是否连接了机器人
    static int plc_bool;//是否连接了机器人
    static int robot_104;//控制字

    static int activeCheckboxCount;// 获取当前选中的复选框个数

    void calculation();//根据控制字判断
    void newDataBase();
    void pangduan();



    QString xunjianpath;
    QStringList xunjian_stringlist;
    int xunjian_count;
    QVector <int> xunjian_points;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void Paint();


private slots:

    //更新表格数据
    void flushValue();
    //触发子页面
    void on_poiling_Action_triggered();

    void on_history_Action_triggered();

    void on_alarm_Action_triggered();

    void on_robot_Action_triggered();

    void on_moniguiji_Actiom_triggered();

    //void on_cam_Action_triggered();

    void on_Ppanel_Action_triggered();

    void on_Rpanel_Action_triggered();

    void on_Ppanel_Action_2_triggered();

    //运动控制
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_btn_LUP_clicked();
    void on_btn_UP_clicked();
    void on_btn_RUP_clicked();
    void on_btn_L_clicked();
    void on_btn_R_clicked();
    void on_btn_LD_clicked();
    void on_btn_D_clicked();
    void on_btn_RD_clicked();

    void on_stop_btn_clicked();
    void on_ZD_btn_clicked();
    void on_ZA_btn_clicked();
    void on_FD_btn_clicked();
    void on_FA_btn_clicked();
    void on_AD_btn_clicked();
    void on_AA_btn_clicked();

    //自动巡检
    void quick_positiving(QStringList stringlist,int count);

    void on_add_Action_triggered();

    void stopxiancheng();

    void startxiancheng();

    void on_checkBox_82_stateChanged(int arg1);

    void on_checkBox_81_stateChanged(int arg1);

    void chufa();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_7_stateChanged(int arg1);

    void on_checkBox_8_stateChanged(int arg1);

    void on_checkBox_9_stateChanged(int arg1);

    void on_kaiqi_caijiqi_7_clicked();

    void on_kaiqi_caijiqi_8_clicked();

    void get_104(int);

//    void on_pushButton_3_clicked();

//    void on_pushButton_4_clicked();

    void on_checkBox_17_stateChanged(int arg1);

    void get_100(int);

    void get_102(int);

    void on_kaiqi_caijiqi_10_clicked();

    void handleTimeout();

    void on_checkBox_10_stateChanged(int arg1);

    void on_checkBox_11_stateChanged(int arg1);

    void on_checkBox_12_stateChanged(int arg1);

    void on_checkBox_13_stateChanged(int arg1);

    void on_checkBox_14_stateChanged(int arg1);

    void on_checkBox_15_stateChanged(int arg1);

    void on_checkBox_16_stateChanged(int arg1);

    void on_checkBox_18_stateChanged(int arg1);

    void on_checkBox_19_stateChanged(int arg1);

    void on_checkBox_20_stateChanged(int arg1);

    void on_actionkong_triggered();

    void on_actionjiqiren_triggered();

    void on_cam_Action_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_checkBox_32_stateChanged(int arg1);

    void on_checkBox_34_stateChanged(int arg1);

    void on_checkBox_35_stateChanged(int arg1);

    void on_checkBox_33_stateChanged(int arg1);

    void on_checkBox_36_stateChanged(int arg1);

    void on_checkBox_37_stateChanged(int arg1);

    void on_checkBox_39_stateChanged(int arg1);

    void on_checkBox_38_stateChanged(int arg1);

    void change_rob(int a);//切换机器人头部

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_41_stateChanged(int arg1);

    void on_checkBox_25_stateChanged(int arg1);

    void on_checkBox_24_stateChanged(int arg1);

    void on_checkBox_27_stateChanged(int arg1);

    void on_checkBox_28_stateChanged(int arg1);

    void on_checkBox_29_stateChanged(int arg1);

    void on_checkBox_42_stateChanged(int arg1);

    void on_checkBox_31_stateChanged(int arg1);

    void on_checkBox_30_stateChanged(int arg1);

    void on_checkBox_21_stateChanged(int arg1);

    void on_checkBox_26_stateChanged(int arg1);

    void on_checkBox_44_stateChanged(int arg1);

    void on_checkBox_40_stateChanged(int arg1);

    void on_checkBox_43_stateChanged(int arg1);

    void on_PLC_action_triggered();

    void chufa1();

signals:
    void send3(int);
    void send(HWND);//发送视频显示控件句柄
    void send_w2(HWND);
    void send2(int);//切换机器人
    void send1();
    void send_rob();//机器人开始工作
    void send4();
    void send5(int);//送入电机转速
    void send6(int,int);//送入自动巡检运动距离
    void send7();
    void send8(float);
    void send9(int);
    void send10(int);//送入自动巡检摄像头定点/连续信号
    void send11(int);//送入自动巡检巡检速度信号
    void send12(int);//送入自动巡检巡检停留时间
    void send13(int);//送入运动控制模式

    void send_plc();//plc开始工作
    void pcl_send4(int);

    void send_allin(int);//送入一键上电值

public slots:

    //接收相机登录句柄
    void rev1(LLONG);
    void rev2(LLONG);

    void send_position(int);
//    void shoudongxunjian_(QStringList);
    void rec_ins(QString string){
        xunjianpath = string;
    };
    void new_path();
    void warning_box(int a);
    void Mrev1(int);

    void heart1(int a);
    //void heart2(int a);
    void rec_robot_connect_bool(bool);//接受机器人连接状态

private:
    Ui::MainWindow *ui;
    LogWidget * m_log;
    inspection * ins;
    history * his;
    moniguiji * moni;
    warning * warn;
    //机器人登录
    robot_login * robot_log;
    //相机登录管理界面
    camera * cameraLogin;
    camera_login * cam_add;
    //相机
    int a;//相机步进
    //创建相机子线程对象
    QThread* t1=new QThread;
    QThread* t2=new QThread;
    QThread* t3=new QThread;
    QThread* t4=new QThread;
    //创建任务类的对象
    cam1* c1=new cam1;
    cam2* c2=new cam2;
    rob1* r1=new rob1;
    plc* p1=new plc;

    QTimer m_timer;
};

#endif // MAINWINDOW_H
