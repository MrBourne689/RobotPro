#ifndef XIANCHENG_H
#define XIANCHENG_H

#include <QObject>
#include <QWidget>
#include "avglobal.h"
#include "dhconfigsdk.h"
#include "dhnetsdk.h"
#define file_PLC "PLC.txt"
#define file_PLC2 "PLC2.txt"
#define file_robot "robot.txt"
//#define IP "192.168.2.109"
#define PORT "37777"
#define USER "admin"
#define PASSWD "admin123"

#include <QTimer>
#include <QModbusDataUnit> //存储接收和发送数据的类，数据类型为1bit和16bit
#include <QModbusReply> //客户端访问服务器后得到的回复（如客户端读服务器数据时包含数据信息）
#include <QMetaType>
#include <QCoreApplication>
#include <QDir>
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

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

extern double_t wendu1;
extern double_t wendu2;
extern double_t wendu3;
extern double_t wendu4;
extern double_t wendu5;
extern double_t wendu6;
extern double_t wendu7;
extern double_t wendu8;

class QModbusClient;
class QModbusReply;

//相机1线程
class cam1 : public QObject
{
    Q_OBJECT
public:
    explicit cam1(QObject *parent = nullptr);

    QString imgPerson;
    QString savefile;
    void SDK();
    void moninit();
    void log();
    void next();
    void cut1();
    void video();
    void cvideo();
    static void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
    static void CALLBACK fRealDataCB(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param,LDWORD dwUser);
    static void CALLBACK HaveReConnect(LLONG lLoginID,char *pchDVRIP,LONG nDVRPort,LDWORD dwUser);

    //    void rev(HWND);
    //    void working();

signals:
    void send(LLONG);//发送登录句柄

public slots:
    void rev1(int);
    void rev(HWND);
    void working();

private:
    char D_Ip[32] ={0};
    char D_UserName[32] = {0};
    char D_Pasdwd[32] = {0};
    int D_Port = 37777;
};

//相机2线程
class cam2 : public QObject
{
    Q_OBJECT
public:
    explicit cam2(QObject *parent = nullptr);

    QString imgPerson;
    QString savefile;
    void SDK();
    void moninit();
    void log2();
    void next2();
    void cut2();
    void video();
    void cvideo();
    static void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
    static void CALLBACK fRealDataCB(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param,LDWORD dwUser);
    static void CALLBACK HaveReConnect(LLONG lLoginID,char *pchDVRIP,LONG nDVRPort,LDWORD dwUser);

    //    void rev(HWND);
    //    void working();

signals:
    void send(LLONG);//发送登录句柄

public slots:
    void rev1(int);
    void rev(HWND);
    void working();

private:
    char D_Ip[32] ={0};
    char D_UserName[32] = {0};
    char D_Pasdwd[32] = {0};
    int D_Port = 37777;
};

//机器人线程
class rob1 : public QObject
{
    Q_OBJECT
public:
    explicit rob1(QObject *parent = nullptr);
    void working();
    void dianji1();
    void dianji2();
    void zhucam();
    void fucam();
    void headlight();
    void backlight();
    void downlight();
    void lianjie();
    void kaiqi();
    void cut3();
    void cut4();
    void write_104(int a);
    static int Value_104;
    static int Value_0;
    void reset();
    void change();
        void yagan1();
        void yagan2();
        void dicam();
        void autoon();
        void saveup();
        void savedown();
        void relay1();
        void relay2();


signals:
    //发出更新信号
    void flush_modbus_value();
    void send_104(int);//发送控制字
    void send_(int);
    void send_100(int);//发送机器人速度
    void send_102(int);//发送机器人方向
    void warning_signal(int a);//报警信号
    void rob_connected(int a);//机器人连接成功！
    void xintiaorob(int);
    //发送机器人连接状态信号
    void send_robot_connect_bool(bool);

public slots:
    void rev2(int);
    void rev1(int);
    //    void lianjie();
    //    void kaiqi();
    void readReady();
    void kaishicaiji();
    void rev3(int);//接收转速
    void rev4(int a,int count);//接受巡检距离
    void rev5(float a);
    void rev6(int a);
    void rev7(int a);//设置自动/定点巡检
    void rev8(int a);//设置自动巡检速度
    void rev9(int a);//设置定点巡检停留时间
    void rev10(int a);//设置定点巡检停留时间
    void allin(int a);//一键上电


private:
    QModbusClient *modbusDevice = nullptr;

};
//PLC线程
class plc : public QObject
{
    Q_OBJECT
public:
    explicit plc(QObject *parent = nullptr);
    void working();
    void lianjie();
    void kaiqi();
    void cut();
    void write(int a,int b);
    void chonddian1();
    void chonddian2();
    void open1();
    void open2();
    void close1();
    void close2();
    void stop1();
    void stop2();
    void up1();
    void up2();
    void down1();
    void down2();
    void pause1();
    void pause2();




signals:
    //发出更新信号
    void flush_modbus_value1();
    void flush_modbus_value2();
    void xintiaoplc(int);
//    void xintiao2(int);


public slots:
    void rev1(int);
    void readReady1();
    void kaishicaiji1();
    void caozuodu();


private:
    QModbusClient *modbusDevice = nullptr;

};
#endif // XIANCHENG_H
