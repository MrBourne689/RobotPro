#include <QtCharts>         // 导入QtCharts所有的头文件，也可以单独导入某一个

// 引入qchart命名空间（注意：如果是在ui中提升为QChartView，
// 则QT_CHARTS_USE_NAMESPACE一定要放在#include "ui_widget.h"前面，否则编译会失败）
QT_CHARTS_USE_NAMESPACE

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include "camera_login.h"
#include "xiancheng.h"
#include "QDebug"
#include "QString"
#include "time.h"
#include "QDateTime"
#include <QSettings>
#include <QStringList>
#include <QFile>
#include <qtextcodec.h>
#include <time.h>

#include <QModbusTcpClient>

int A=1;//总切换
int kozhishu;
int plc_kozhishu;
LLONG LoginHandle1;//相机1登录句柄
LLONG lHandle1;//相机1监视句柄
HWND hWnd1;//相机1主程序视频显示窗口句柄
LLONG LoginHandle2;//相机2登录句柄
LLONG lHandle2;//相机2句柄
HWND hWnd2;//相机2主程序视频显示窗口句柄
int rob1::Value_104=0;//104控制字
int rob1::Value_0=104;//104控制字
int value2=0;
int value2_rob=0;

cam1::cam1(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<__int64>("__int64");
}
//接收视频显示控件句柄
void cam1::rev(HWND a)
{
    qDebug("a=%d", a);
    hWnd1=a;
    qDebug("receive");
}
void cam1::rev1(int a)
{
    A=a;
    qDebug("receive");
    cut1();
}
void cam1::working()
{
    SDK();
    moninit();
    log();
    next();
}
//SDK初始化
void cam1::SDK()
{
    if(CLIENT_Init((fDisConnect)DisConnectFunc, (LDWORD)0))
    {
        qDebug("SDK INIT OK!");
    }
    else
    {
        qDebug("SDK INIT FAIL!");
    }
}
void cam1::moninit()
{
    //获取SDK版本信息
    DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
    printf("NetSDK version is [%d]\n",dwNetSdkVersion);
    //设置断线重连回调接口，设置过断线重连成功回调函数后，当设备出现断线情况，SDK内部会自动进行重连操作
    CLIENT_SetAutoReconnect(&HaveReConnect,0);
    //设置登录超时时间和尝试次数
    int nWaitTime = 5000; //登录请求响应超时时间设置为5s
    int nTryTimes = 3; //登录时尝试建立连接3次
    CLIENT_SetConnectTime(nWaitTime,nTryTimes);
    //设置更多网络参数，NET_PARAM的nWaittime,nConnectTryNum成员与CLIENT_SetConnectTime接口设置的登录设备超时时间和尝试次数的意义相同
    NET_PARAM stuNetparm ={0};
    stuNetparm.nConnectTime = 3000;//登录时尝试建立连接的超时时间
    CLIENT_SetNetworkParam(&stuNetparm);
}
//登录相机1
void cam1::log()
{
    QString IP1;
    if(A==1)
    {
        //读取IP 端口号 用户名 密码
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QDataStream dataStr(&file);
        QString ip3,port3,name3,password3;
        for(int i = 0 ; i< 3 ;i++){
            dataStr>>ip3>>port3>>name3>>password3;
            //qDebug()<<i<<ip3<<port3<<name3<<password3;
        }
        file.close();
        qDebug()<<"3:"<<ip3<<port3<<name3<<password3;
        IP1 = ip3;
    }
    else
    {
        //读取IP 端口号 用户名 密码
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QDataStream dataStr(&file);
        QString ip5,port5,name5,password5;
        for(int i=0; i<5; i++){
            dataStr>>ip5>>port5>>name5>>password5;
        }
        file.close();
        qDebug()<<"5:"<<ip5<<port5<<name5<<password5;
        IP1 = ip5;
    }
    qDebug()<<"ip1:"<<IP1;
    QByteArray ba = IP1.toLocal8Bit();
    memcpy(D_Ip,ba.data(),ba.size()+1);
    strcpy(D_UserName,USER);
    strcpy(D_Pasdwd,PASSWD);
    //    qDebug("D_Ip1=%d", D_Ip);
    //    qDebug()<<D_Ip;
    //    qDebug()<<D_UserName;
    //    qDebug()<<D_Pasdwd;
    //    qDebug()<<D_Port;
    // 登录
    NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY stInparam;
    memset(&stInparam, 0, sizeof(stInparam));
    stInparam.dwSize = sizeof(stInparam);
    strncpy(stInparam.szIP, D_Ip, sizeof(stInparam.szIP) - 1);
    strncpy(stInparam.szPassword, D_Pasdwd, sizeof(stInparam.szPassword) - 1);
    strncpy(stInparam.szUserName, D_UserName, sizeof(stInparam.szUserName) - 1);
    stInparam.nPort = D_Port;
    stInparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;
    NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY stOutparam;
    LoginHandle1 = CLIENT_LoginWithHighLevelSecurity(&stInparam, &stOutparam);


    qDebug()<<"---------------------------------------";
    qRegisterMetaType<__int64>("__int64");

    emit send(LoginHandle1);
    qDebug()<<"send LoginHandle1="<<LoginHandle1;


    if (LoginHandle1)
    {
        printf("Login successful\n");
    }
    else
    {
        printf("login fail\n");
    }
}
//开始监视1
void cam1::next()
{
    if(FALSE == LoginHandle1)
    {
        //        QMessageBox::about(NULL,laddr->text(),"连接失败");
        return;
    }
    //获取frame句柄
    HWND hWnd;/* = (HWND)ui->frame->winId();*/
    hWnd=hWnd1;
    qDebug("hWnd1=%d", hWnd1);
    qDebug("hWnd=%d", hWnd);
    //监视
    lHandle1 = CLIENT_RealPlayEx(LoginHandle1,0, hWnd);//实时监视句柄
    qDebug()<<"lHandle"<<lHandle1<<endl;
    if (lHandle1)
    {
        qDebug ("CLIENT_RealPlayEx success!");
        //设置实时监视回调函数
        DWORD dwFlag = REALDATA_FLAG_RAW_DATA;//原始数据标志
        CLIENT_SetRealDataCallBackEx2(lHandle1, &fRealDataCB, NULL,dwFlag);
    }
    else
    {
        printf("CLIENT_RealPlayEx: failed! Error code: %x.\n",CLIENT_GetLastError());
    }
}
//录制视频
void cam1::video()
{
    //    InitSet();
    QDateTime currenttime = QDateTime::currentDateTime();
    QString imgtime =currenttime.toString("yyyyMMddhhmmss");
    //       ....................................................................视频保存
    //savefile="E:/shipin";
    QDir dir;
    QString currerntDir = dir.currentPath();

    // 检查目录是否存在，若不存在则新建
    QString dir_str = currerntDir+"/video/";
    if(!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
    }
    QString imgname1 = currerntDir+"/video/"+imgtime+".dav";
    //QString imgname1 = "./"+imgtime+".dav";
    //QString转换为const char
    std::string str1 = imgname1.toStdString();
    const char *mvFileName1 = str1.c_str();
    //    qDebug()<<"mvFileName1"<<mvFileName1<<endl;
    //    qDebug()<<"lHandle"<<lHandle<<endl;
    //    BOOL bRet0 =CLIENT_CapturePictureEx(lHandle,mvFileName1,NET_CAPTURE_JPEG);
    BOOL bRet0 = CLIENT_SaveRealData(lHandle1,mvFileName1);
    qDebug("bRet0=%d", bRet0);
    qDebug("开始录制");
}
//停止录制
void cam1::cvideo()
{
    BOOL bRet0 = CLIENT_StopSaveRealData(lHandle1);
    qDebug("bRet0=%d", bRet0);
}
//数据回调
void CALLBACK cam1::fRealDataCB(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param,LDWORD dwUser)
{
    //   qDebug("1");
    //    printf("receive real data,param:lRealHandle[%p],dwDataType[%d],pBuffer[%p],dwBufSize[%d]\n",lRealHandle,dwDataType,pBuffer,dwBufSize);
    //    if(CLIENT_SaveRealData(lHandle,"D:/test.mp4"))
    //    {
    //        printf("Save data success\n");

    //    }
}
//重连回调
void CALLBACK cam1::HaveReConnect(LLONG lLoginID,char *pchDVRIP,LONG nDVRPort,LDWORD dwUser)
{
    printf("Call HaveReConnect\n");
    printf("lLoginID[0x%x]",lLoginID);
    if(NULL != pchDVRIP)
    {
        printf("pchDVRIP[%s]\n",pchDVRIP);
    }
    printf("nDVRPort[%d]\n",nDVRPort);
    printf("dwUser[%p]\n",dwUser);
    printf("\n");
}
//SDK回调函数
void CALLBACK cam1::DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser) {
    printf("Call DisConnectFunc\n");
    printf("lLoginID[0x%x]",lLoginID);
    if(NULL != pchDVRIP)     {
        printf("pchDVRIP[%s]\n",pchDVRIP);
    }
    printf("nDVRPort[%d]\n",nDVRPort);
    //printf("dwUser[%p]\n",dwUser);
    printf("\n");
}
//关闭相机
void cam1::cut1()
{
    CLIENT_StopRealPlayEx(lHandle1);
    CLIENT_Logout(LoginHandle1);
    //清理SDK资源
    CLIENT_Cleanup();
    qDebug()<<"-----------切断摄像头1";
}

cam2::cam2(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<__int64>("__int64");
}
//接收视频显示控件句柄
void cam2::rev(HWND a)
{
    hWnd2=a;
}
void cam2::rev1(int a)
{
    A=a;
    qDebug("receive");
    cut2();
}
void cam2::working()
{
    SDK();
    moninit();
    log2();
    next2();
}
//SDK初始化
void cam2::SDK()
{
    if(CLIENT_Init((fDisConnect)DisConnectFunc, (LDWORD)0))
    {
        qDebug("SDK INIT OK!");
    }
    else
    {
        qDebug("SDK INIT FAIL!");
    }
}
void cam2::moninit()
{
    //获取SDK版本信息
    DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
    printf("NetSDK version is [%d]\n",dwNetSdkVersion);
    //设置断线重连回调接口，设置过断线重连成功回调函数后，当设备出现断线情况，SDK内部会自动进行重连操作
    CLIENT_SetAutoReconnect(&HaveReConnect,0);
    //设置登录超时时间和尝试次数
    int nWaitTime = 5000; //登录请求响应超时时间设置为5s
    int nTryTimes = 3; //登录时尝试建立连接3次
    CLIENT_SetConnectTime(nWaitTime,nTryTimes);
    //设置更多网络参数，NET_PARAM的nWaittime,nConnectTryNum成员与CLIENT_SetConnectTime接口设置的登录设备超时时间和尝试次数的意义相同
    NET_PARAM stuNetparm ={0};
    stuNetparm.nConnectTime = 3000;//登录时尝试建立连接的超时时间
    CLIENT_SetNetworkParam(&stuNetparm);
}
//登录相机2
void cam2::log2()
{
    QString IP2;
    if(A==1)
    {
        //读取IP 端口号 用户名 密码
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QDataStream dataStr(&file);
        QString ip4,port4,name4,password4;
        for(int i=0; i<4;i++ ){
            dataStr>>ip4>>port4>>name4>>password4;
        }
        file.close();
        qDebug()<<"4:"<<ip4<<port4<<name4<<password4;
        IP2 = ip4;
    }
    else
    {
        //读取IP 端口号 用户名 密码
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QDataStream dataStr(&file);
        QString ip6,port6,name6,password6;
        for(int i=0; i<6; i++){
            dataStr>>ip6>>port6>>name6>>password6;
        }
        file.close();
        qDebug()<<"6:"<<ip6<<port6<<name6<<password6;
        IP2 = ip6;
    }
    qDebug()<<"ip2:"<<IP2;
    QByteArray ba = IP2.toLocal8Bit();
    memcpy(D_Ip,ba.data(),ba.size()+1);
    strcpy(D_UserName,USER);
    strcpy(D_Pasdwd,PASSWD);
    //    qDebug("D_Ip2=%d", D_Ip);
    //    qDebug()<<D_Ip;
    //    qDebug()<<D_UserName;
    //    qDebug()<<D_Pasdwd;
    //    qDebug()<<D_Port;
    // 登录
    NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY stInparam;
    memset(&stInparam, 0, sizeof(stInparam));
    stInparam.dwSize = sizeof(stInparam);
    strncpy(stInparam.szIP, D_Ip, sizeof(stInparam.szIP) - 1);
    strncpy(stInparam.szPassword, D_Pasdwd, sizeof(stInparam.szPassword) - 1);
    strncpy(stInparam.szUserName, D_UserName, sizeof(stInparam.szUserName) - 1);
    stInparam.nPort = D_Port;
    stInparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;
    NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY stOutparam;
    LoginHandle2 = CLIENT_LoginWithHighLevelSecurity(&stInparam, &stOutparam);
    emit send(LoginHandle2);
    qDebug()<<"send LoginHandle2="<<LoginHandle2;
    if (LoginHandle2)
    {
        printf("Login successful\n");
    }
    else
    {
        printf("login fail\n");
    }
}
//开始监视2
void cam2::next2()
{
    if(FALSE == LoginHandle2)
    {
        //        QMessageBox::about(NULL,laddr->text(),"连接失败");
        return;
    }
    //获取frame句柄
    HWND hWnd;/* = (HWND)ui->frame->winId();*/
    hWnd=hWnd2;
    //qDebug("hWnd2=%d", hWnd);
    //监视
    lHandle2 = CLIENT_RealPlayEx(LoginHandle2,0, hWnd);//实时监视句柄
    //qDebug()<<"lHandle"<<lHandle2<<endl;
    if (lHandle2)
    {
        qDebug ("CLIENT_RealPlayEx success!");
        //设置实时监视回调函数
        DWORD dwFlag = REALDATA_FLAG_RAW_DATA;//原始数据标志
        CLIENT_SetRealDataCallBackEx2(lHandle2, &fRealDataCB, NULL,dwFlag);
    }
    else
    {
        printf("CLIENT_RealPlayEx: failed! Error code: %x.\n",CLIENT_GetLastError());
    }
}
//录制视频
void cam2::video()
{
    //    InitSet();
    QDateTime currenttime = QDateTime::currentDateTime();
    QString imgtime =currenttime.toString("yyyyMMddhhmmss");
    //       ....................................................................视频保存
    //savefile="E:/shipin";
    QDir dir;
    QString currerntDir = dir.currentPath();

    // 检查目录是否存在，若不存在则新建
    QString dir_str = currerntDir+"/video/";
    if(!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
    }
    QString imgname1 = currerntDir+"/video/"+imgtime+".dav";
    //QString转换为const char
    std::string str1 = imgname1.toStdString();
    const char *mvFileName1 = str1.c_str();
    //    qDebug()<<"mvFileName1"<<mvFileName1<<endl;
    //    qDebug()<<"lHandle"<<lHandle<<endl;
    //    BOOL bRet0 =CLIENT_CapturePictureEx(lHandle,mvFileName1,NET_CAPTURE_JPEG);
    BOOL bRet0 = CLIENT_SaveRealData(lHandle2,mvFileName1);
    //qDebug("bRet0=%d", bRet0);
    qDebug("开始录制");
}
//停止录制
void cam2::cvideo()
{
    BOOL bRet0 = CLIENT_StopSaveRealData(lHandle2);
    //qDebug("bRet0=%d", bRet0);
    qDebug("停止录制");
}
//数据回调
void CALLBACK cam2::fRealDataCB(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param,LDWORD dwUser)
{
    //   qDebug("1");
    //    printf("receive real data,param:lRealHandle[%p],dwDataType[%d],pBuffer[%p],dwBufSize[%d]\n",lRealHandle,dwDataType,pBuffer,dwBufSize);
    //    if(CLIENT_SaveRealData(lHandle,"D:/test.mp4"))
    //    {
    //        printf("Save data success\n");

    //    }
}
//重连回调
void CALLBACK cam2::HaveReConnect(LLONG lLoginID,char *pchDVRIP,LONG nDVRPort,LDWORD dwUser)
{
    printf("Call HaveReConnect\n");
    printf("lLoginID[0x%x]",lLoginID);
    if(NULL != pchDVRIP)
    {
        printf("pchDVRIP[%s]\n",pchDVRIP);
    }
    printf("nDVRPort[%d]\n",nDVRPort);
    printf("dwUser[%p]\n",dwUser);
    printf("\n");
}
//SDK回调函数
void CALLBACK cam2::DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser) {
    printf("Call DisConnectFunc\n");
    printf("lLoginID[0x%x]",lLoginID);
    if(NULL != pchDVRIP)     {
        printf("pchDVRIP[%s]\n",pchDVRIP);
    }
    printf("nDVRPort[%d]\n",nDVRPort);
    //printf("dwUser[%p]\n",dwUser);
    printf("\n");
}
//关闭相机
void cam2::cut2()
{
    CLIENT_StopRealPlayEx(lHandle2);
    CLIENT_Logout(LoginHandle2);
    //清理SDK资源
    CLIENT_Cleanup();
    qDebug()<<"-----------切断摄像头2";
}

rob1::rob1(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<__int64>("__int64");
    modbusDevice = new QModbusTcpClient(this);
}


void rob1::rev1(int a)
{
    A=a;
    qDebug("receive");
}
void rob1::rev2(int a)
{
    kozhishu=a;
    qDebug("我you被触发了");
    dianji1();
    dianji2();
    zhucam();
    fucam();
    headlight();
    backlight();
    downlight();
    change();
    reset();

    //allin();//一键上电
    yagan1();
    yagan2();
    dicam();
    autoon();
    saveup();
    savedown();
    relay1();
    relay2();
}

void rob1::working()
{
    lianjie();
}

void rob1::kaiqi()
{
    kaishicaiji();
    qDebug()<<"START";
    QTimer *timer = new QTimer(); //this 为parent类, 表示当前窗口
    connect(timer, SIGNAL(timeout()), this, SLOT(kaishicaiji()));// SLOT填入一个槽函数
    timer->start(1000); // 1000毫秒, 等于 1 秒
}

void rob1::lianjie()
{
    QString IP3;
    if(A==1)
    {
        //读取IP 端口号 用户名 密码
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QDataStream dataStr(&file);
        QString ip,port,name,password;
        dataStr>> ip >> port >> name >> password;
        file.close();
        //qDebug()<<ip<<port<<name<<password;
        IP3 = ip;
    }
    else
    {
        //读取IP 端口号 用户名 密码
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QDataStream dataStr(&file);
        QString ip0,port0,name0,password0,ip,port,name,password;
        dataStr>> ip0 >> port0 >> name0 >> password0>> ip >> port >> name >> password;
        file.close();
        IP3 = ip;
    }
    qDebug()<<"ip3"<<IP3;
    if (!modbusDevice)
    {
        emit rob_connected(0);
        return;
    }
    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        //处于非连接状态，进行连接
        //TCP连接,端口502，地址127.0.0.1   192.168.2.100
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, IP3);
        //连接超时设置，2000ms
        qDebug("10");
        modbusDevice->setTimeout(2000);
        //连接失败重试连接，3次
        modbusDevice->setNumberOfRetries(3);
        //调试窗口显示连接状态
        if (modbusDevice->connectDevice()) {
            qDebug()<< "Connected!";
        }
        if (modbusDevice->state())
        {
            if(A==1)
            {
                emit rob_connected(1);
            }
            else
            {
                emit rob_connected(2);
            }
        }
    }
    else {
        //处在连接状态进行断开连接的操作
        //modbusDevice->disconnectDevice();
    }
    kaiqi();
}

void rob1::cut3()
{
    if(A==1){
        emit rob_connected(3);
    }
    else
    {
        emit rob_connected(4);
    }
    //    modbusDevice->disconnectDevice();
}

void rob1::cut4()
{
    modbusDevice->disconnectDevice();
    qDebug()<< "关闭机器人";
}

//从服务器读数据的读按钮槽方法
void rob1::kaishicaiji()
{
    value2_rob=value2_rob+1;
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        emit rob_connected(0);
        return;
    }

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qDebug()<< "robot not Connected!";//机器人连接状态发送到主页
        emit send_robot_connect_bool(false);//机器人连接状态发送到主页
    }
    else
    {
        qDebug()<< "robot Connected!";//机器人连接状态发送到主页
        emit send_robot_connect_bool(true);//机器人连接状态发送到主页
    }

    //从寄存器地址0开始连续读取22个数
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters,0,106);
    qDebug()<<"机器人采集22个数";
    if (auto *reply = modbusDevice->sendReadRequest(readUnit,1)) {
        if (!reply->isFinished())
        {
            qDebug()<<"机器人连接了";
            emit xintiaorob(1);
            connect(reply, &QModbusReply::finished, this, &rob1::readReady);
        }
        else
            delete reply; // broadcast replies return immediately
    }
}

//在这里读的数据
void rob1::readReady()
{
    //QModbusReply这个类存储了来自client的数据,sender()返回发送信号的对象的指针
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
    {
        return;
    }

    //数据从QModbusReply这个类的result方法中获取,也就是本程序中的reply->result()
    //判断是否出错
    const QModbusDataUnit unit = reply->result();

    Value_104 = unit.value(104);
    //qDebug()<<"Value_104赋值为："<<Value_104;
    int value2_yu;
    value2_yu=value2_rob % 5;
    qDebug() << "value2_yu为： " << value2_yu;
    if (value2_yu==0)
    {
        qDebug() << "进入延时";
        emit(send_104(Value_104));//发送控制字
        emit(send_100(unit.value(100)));//发送机器人速度
        qDebug()<<"发送机器人速度"<<unit.value(107);
        emit(send_102(unit.value(102)));//发送机器人方向
    }
    //    emit(send_104(Value_104));//发送控制字
    //    emit(send_100(unit.value(100)));//发送机器人速度
    //    qDebug()<<"发送机器人速度"<<unit.value(107);
    //    emit(send_102(unit.value(102)));//发送机器人方向
    emit(send_(unit.value(7)));//发送当前位署

    //写入txt
    QFile file(file_robot);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream dataStr(&file);


    uint16_t var1 = unit.value(0);
    uint16_t var2 = unit.value(1);
    uint32_t var12 = (var1 << 16) +  var2;
    dataStr<<QString::number(var12);
    //qDebug()<<"32位var3 = (var1 << 16) +  var2"<<var3<<var1<<var2;
    uint16_t var3 = unit.value(2);
    uint16_t var4 = unit.value(3);
    uint32_t var34 = (var3 << 16) +  var4;
    dataStr<<QString::number(var34);

    uint16_t var5 = unit.value(4);
    uint16_t var6 = unit.value(5);
    uint32_t var56 = (var5 << 16) +  var6;
    dataStr<<QString::number(var56);

    uint16_t var7 = unit.value(6);
    uint16_t var8 = unit.value(7);
    uint32_t var78 = (var7 << 16) +  var8;
    dataStr<<QString::number(var78);

    for(int i=8;i<21;i++)
    {
        dataStr<<QString::number(unit.value(i));
    }
    file.close();


    //创建数据库并连接
    QSqlDatabase database_rob;
    if (QSqlDatabase::contains("rob_connection"))
    {
        database_rob = QSqlDatabase::database("rob_connection");
    }
    else
    {
        database_rob = QSqlDatabase::addDatabase("QSQLITE","rob_connection");
        database_rob.setDatabaseName("MyDataBase.db");
        database_rob.setUserName("HeFanRobot");
        database_rob.setPassword("123456");
    }
    //判断数据库连接
    if (!database_rob.open())
    {
        qDebug() << "子线程Error: Failed to connect database." << database_rob.lastError();
    }
    else
    {
        //qDebug()<<"子线程DataBase open sucess!";
    }


    QSqlQuery sql_query(QSqlDatabase::database("rob_connection"));
    QString str_sql = "";
    //查询最大id
    QString select_max_sql = "select max(id) from student";
    int max_id = 0;
    sql_query.prepare(select_max_sql);
    if(!sql_query.exec())
    {
        qDebug() <<"子线程Error:"<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            max_id = sql_query.value(0).toInt();
        }
    }

    //插入数据
    QDateTime time= QDateTime::currentDateTime();//获取系统当前的时间
    QString query_time1 = time.toString("yyyy-MM-dd");//格式化日期
    QString query_time2 = time.toString("yyyyMMddhhmmss");//格式化时间

    str_sql = QString("insert into student values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,%13)")
            .arg(max_id+1).arg(query_time1).arg(query_time2)
            .arg(unit.value(8)).arg(unit.value(11))
            .arg(unit.value(13)).arg(unit.value(14))
            .arg(unit.value(15)).arg(unit.value(16))
            .arg(unit.value(17)).arg(unit.value(18))
            .arg(unit.value(19)).arg(QString::number(var78));

    //qDebug()<<"str_sql"<<str_sql;
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"子线程插入数据1失败！！"<< sql_query.lastError();
    }
    else
    {
        //qDebug()<<"插入数据1成功";

    }


    str_sql = "select * from warningValue";

    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"查询失败！！";
        return;
    }
    else
    {
        while(sql_query.next())
        {
            if(unit.value(8) < sql_query.value(3).toInt() || unit.value(8) > sql_query.value(4).toInt() ||
                    unit.value(11) < sql_query.value(5).toInt() || unit.value(11) > sql_query.value(6).toInt() ||
                    unit.value(13) < sql_query.value(7).toInt() || unit.value(13) > sql_query.value(8).toInt() ||
                    unit.value(14) < sql_query.value(9).toInt() || unit.value(14) > sql_query.value(10).toInt() ||
                    unit.value(15) < sql_query.value(11).toInt() || unit.value(15) > sql_query.value(12).toInt() ||
                    unit.value(16) < sql_query.value(13).toInt() || unit.value(16) > sql_query.value(14).toInt() ||
                    unit.value(17) < sql_query.value(15).toInt() || unit.value(17) > sql_query.value(16).toInt() ||
                    unit.value(18) < sql_query.value(17).toInt() || unit.value(18) > sql_query.value(18).toInt() ||
                    unit.value(19) < sql_query.value(19).toInt() || unit.value(19) > sql_query.value(20).toInt()
                    )
            {
                //报警弹窗
                //qDebug()<<"rob1警告,存在数值超出预警值！";;
                emit warning_signal(1);
                //写入数据库
                //查询最大id
                QString select_max_sql = "select max(id) from warning";
                int max_id = 0;
                sql_query.prepare(select_max_sql);
                if(!sql_query.exec())
                {
                    qDebug() <<"子线程Error:"<<sql_query.lastError();
                }
                else
                {
                    while(sql_query.next())
                    {
                        max_id = sql_query.value(0).toInt();
                    }
                }

                //插入数据
                //                QDateTime time2= QDateTime::currentDateTime();//获取系统当前的时间
                //                query_time1 = time2.toString("yyyy-MM-dd");//格式化日期
                //                query_time2 = time2.toString("yyyyMMddhhmmss");//格式化时间

                str_sql = QString("insert into warning values(%1,'%2','%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,%13)")
                        .arg(max_id+1).arg(query_time1).arg(query_time2)
                        .arg(unit.value(8)).arg(unit.value(11))
                        .arg(unit.value(13)).arg(unit.value(14))
                        .arg(unit.value(15)).arg(unit.value(16))
                        .arg(unit.value(17)).arg(unit.value(18))
                        .arg(unit.value(19)).arg(QString::number(var78));

                if(!sql_query.exec(str_sql))
                {
                    qDebug()<<"子线程插入数据1失败！！"<< sql_query.lastError();
                }
                else
                {
                    //qDebug()<<"插入数据1成功";

                }

            }
            else
            {
                emit warning_signal(1);
            }
        }
    }

    database_rob.close();
    int value2_yu2;
    value2_yu2=value2_rob % 5;
    qDebug() << "value2_yu2为： " << value2_yu2;
    if (value2_yu2==0)
    {
        emit flush_modbus_value();
    }
}
//1#2#电机上电
void rob1::dianji1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }

    if(kozhishu==1)
    {
        Value_104=Value_104+1;
        write_104(Value_104);
    }
    if(kozhishu==2)
    {
        Value_104=Value_104-1;
        write_104(Value_104);
    }
}

//3#4#电机上电
void rob1::dianji2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }

    if(kozhishu==3)
    {
        Value_104=Value_104+2;
        write_104(Value_104);
    }
    if(kozhishu==4)
    {
        Value_104=Value_104-2;
        write_104(Value_104);
    }
}

//电动推杆压紧
void rob1::yagan1()
{

    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }

    if(kozhishu==24)
    {
        Value_104=Value_104+4;
        write_104(Value_104);
    }
    if(kozhishu==25)
    {
        Value_104=Value_104-4;
        write_104(Value_104);
    }
}

//电动推杆松开
void rob1::yagan2()
{

    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }

    if(kozhishu==26)
    {
        Value_104=Value_104+8;
        write_104(Value_104);
    }
    if(kozhishu==27)
    {
        Value_104=Value_104-8;
        write_104(Value_104);
    }
}

//前灯上电
void rob1::headlight()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==13)
    {
        Value_104=Value_104+16;
        write_104(Value_104);
    }
    if(kozhishu==14)
    {
        Value_104=Value_104-16;
        write_104(Value_104);
    }
}

//后灯上电
void rob1::backlight()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==15)
    {
        Value_104=Value_104+32;
        write_104(Value_104);
    }
    if(kozhishu==16)
    {
        Value_104=Value_104-32;
        write_104(Value_104);
    }
}
//底灯上电
void rob1::downlight()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==17)
    {
        Value_104=Value_104+64;
        write_104(Value_104);
    }
    if(kozhishu==18)
    {
        Value_104=Value_104-64;
        write_104(Value_104);
    }
}
//前摄像头上电
void rob1::zhucam()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==9)
    {
        Value_104=Value_104+128;
        write_104(Value_104);
    }
    if(kozhishu==10)
    {
        Value_104=Value_104-128;
        write_104(Value_104);
    }
}
//后摄像头上电
void rob1::fucam()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==11)
    {
        Value_104=Value_104+256;
        write_104(Value_104);
    }
    if(kozhishu==12)
    {
        Value_104=Value_104-256;
        write_104(Value_104);
    }
}
//底摄像头上电
void rob1::dicam()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==28)
    {
        Value_104=Value_104+512;
        write_104(Value_104);
    }
    if(kozhishu==29)
    {
        Value_104=Value_104-512;
        write_104(Value_104);
    }
}
//自动-启动
void rob1::autoon()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==30)
    {
        Value_104=Value_104+1024;
        write_104(Value_104);
    }
    if(kozhishu==31)
    {
        Value_104=Value_104-1024;
        write_104(Value_104);
    }
}

//一键上电
void rob1::allin(int a)
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    Value_104=Value_104+a;
    write_104(Value_104);
}
//救援机构抬起
void rob1::saveup()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==32)
    {
        Value_104=Value_104+4096;
        write_104(Value_104);
    }
    if(kozhishu==33)
    {
        Value_104=Value_104-4096;
        write_104(Value_104);
    }
}
//救援机构落下
void rob1::savedown()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==34)
    {
        Value_104=Value_104+8192;
        write_104(Value_104);
    }
    if(kozhishu==35)
    {
        Value_104=Value_104-8192;
        write_104(Value_104);
    }
}
//1#继电器
void rob1::relay1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==36)
    {
        Value_104=Value_104+16384;
        write_104(Value_104);
    }
    if(kozhishu==37)
    {
        Value_104=Value_104-16384;
        write_104(Value_104);
    }
}
//2#继电器
void rob1::relay2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==38)
    {
        Value_104=Value_104+32768;
        write_104(Value_104);
    }
    if(kozhishu==39)
    {
        Value_104=Value_104-32768;
        write_104(Value_104);
    }
}
//改变方向
void rob1::change()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==20)
    {
        QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 102, 1);
        writeData.setValue(0,1);
        qDebug() << "发送的数据为： " << writeData.values();
        QModbusReply* reply = modbusDevice->sendWriteRequest(writeData, 1);
        if (reply)
        {
            if (!reply->isFinished())
            {
                //接收响应信息
                connect(reply, &QModbusReply::finished, this, [this, reply](){
                    if (reply->error() == QModbusDevice::ProtocolError)
                    {
                        //接收到的响应信息是协议错误
                        qDebug() << "写入数据错误：" << reply->errorString();
                    }
                    else if (reply->error() != QModbusDevice::NoError)
                    {
                        //接收到的响应消息是其它错误
                        qDebug() << "写入数据错误： " << reply->errorString();
                    }
                    else
                    {
                        //接收到的消息没有错误 一般没有必要解析响应消息
                        const QModbusDataUnit data = reply->result();

                        qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                    }

                    reply->deleteLater();
                });
            }
            else
            {
                //发送没有响应数据
                //broadcast replies return immediately
                reply->deleteLater();
            }
        }
        else
        {
            qDebug() << "sendWriteRequest Error: " << reply->errorString();
        }
    }
    if(kozhishu==21)
    {
        QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 102, 1);
        writeData.setValue(0,0);
        qDebug() << "发送的数据为： " << writeData.values();
        QModbusReply* reply = modbusDevice->sendWriteRequest(writeData, 1);
        if (reply)
        {
            if (!reply->isFinished())
            {
                //接收响应信息
                connect(reply, &QModbusReply::finished, this, [this, reply](){
                    if (reply->error() == QModbusDevice::ProtocolError)
                    {
                        //接收到的响应信息是协议错误
                        qDebug() << "写入数据错误：" << reply->errorString();
                    }
                    else if (reply->error() != QModbusDevice::NoError)
                    {
                        //接收到的响应消息是其它错误
                        qDebug() << "写入数据错误： " << reply->errorString();
                    }
                    else
                    {
                        //接收到的消息没有错误 一般没有必要解析响应消息
                        const QModbusDataUnit data = reply->result();

                        qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                    }

                    reply->deleteLater();
                });
            }
            else
            {
                //发送没有响应数据
                //broadcast replies return immediately
                reply->deleteLater();
            }
        }
        else
        {
            qDebug() << "sendWriteRequest Error: " << reply->errorString();
        }
    }
}
//写入104
void rob1::write_104(int a)
{
    //从地址104开始写1个寄存器的值
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 104, 1);
    writeData.setValue(0,a);
    qDebug() << "Value_104"
                "为： " << a;
    qDebug() << "发送的数据为： " << writeData.values();
    QModbusReply* reply = modbusDevice->sendWriteRequest(writeData, 1);
    if (reply)
    {
        if (!reply->isFinished())
        {
            //接收响应信息
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
        else
        {
            //发送没有响应数据
            //broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else
    {
        qDebug() << "sendWriteRequest Error: " << reply->errorString();
    }
}

//初始化104，置零，全部断电
void rob1::reset()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(kozhishu==19)
    {
        Value_104=0;
        write_104(Value_104);
        //emit(send_104(Value_104));//发送控制字
    }
}


//电机旋转
void rob1::rev3(int a)
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    //传递电机转速
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 100, 1);
    //    float data = a*10000;
    writeData.setValue(0,a);
    qDebug()<<"电机转速:"<<a;
    qDebug() << "发送的数据为： " << writeData.values();
    QModbusReply* reply = modbusDevice->sendWriteRequest(writeData, 1);


    if (reply)
    {
        if (!reply->isFinished())
        {
            //接收响应信息
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
        else
        {
            //发送没有响应数据
            //broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else
    {
        qDebug() << "sendWriteRequest Error: " << reply->errorString();
    }
}
//自动巡检
void rob1::rev4(int a,int count){
    qDebug()<<a;
    qDebug()<<count;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 120+(count*2), 1);
    //    int data =a*1000;
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}
void rob1::rev5(float a)
{
    qDebug()<<"okkk";
    qDebug()<<a;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 118, 1);
    //    int data =a*1000;
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}
//自动巡检任务点数
void rob1::rev6(int a)
{
    qDebug()<<"okkk";
    qDebug()<<a;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 105, 1);
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}
void rob1::rev7(int a)
{
    qDebug()<<"okkk";
    qDebug()<<a;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 108, 1);
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}
void rob1::rev8(int a)
{
    qDebug()<<a;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 107, 1);
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}
void rob1::rev9(int a){
    qDebug()<<a;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 106, 1);
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}
void rob1::rev10(int a){
    qDebug()<<a;
    QModbusDataUnit writedata(QModbusDataUnit::HoldingRegisters, 101, 1);
    qDebug()<<"待写入参数机器人运动模式为"<<a;
    writedata.setValue(0,a);
    QModbusReply* reply = modbusDevice->sendWriteRequest(writedata, 1);
    if(reply){
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
    }
}

plc::plc(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<__int64>("__int64");
    modbusDevice = new QModbusTcpClient(this);
}

void plc::working()
{
    lianjie();
}

void plc::kaiqi()
{
    kaishicaiji1();
    qDebug()<<"START";
    QTimer *timer = new QTimer(); //this 为parent类, 表示当前窗口
    connect(timer, SIGNAL(timeout()), this, SLOT(kaishicaiji1()));// SLOT填入一个槽函数
    timer->start(1000); // 1000毫秒, 等于 1 秒

    //    QTimer *timer2 = new QTimer(); //this 为parent类, 表示当前窗口
    //    connect(timer2, SIGNAL(timeout()), this, SLOT(caozuodu()));// SLOT填入一个槽函数
    //    timer2->start(3000); // 1000毫秒, 等于 1 秒

}

void plc::lianjie()
{
    QString IP;
    //读取IP 端口号 用户名 密码
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QDataStream dataStr(&file);
    QString ip3,port3,name3,password3;
    for(int i = 0 ; i< 7 ;i++){
        dataStr>>ip3>>port3>>name3>>password3;
        //qDebug()<<i<<ip3<<port3<<name3<<password3;
    }
    file.close();
    qDebug()<<"3:"<<ip3<<port3<<name3<<password3;
    IP = ip3;
    QString ip0,port0,name0,password0,ip,port,name,password;
    qDebug()<<"ip3"<<IP;
    if (!modbusDevice)
    {
        return;
    }
    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        //处于非连接状态，进行连接
        //TCP连接,端口502，地址127.0.0.1   192.168.2.100
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 503);
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, IP);
        //连接超时设置，2000ms
        qDebug("10");
        modbusDevice->setTimeout(2000);
        //连接失败重试连接，3次
        modbusDevice->setNumberOfRetries(3);
        //调试窗口显示连接状态
        if (modbusDevice->connectDevice()) {
            qDebug()<< "Connected!";
        }
        if (modbusDevice->state())
        {

        }
    }
    else {
        //处在连接状态进行断开连接的操作
        //modbusDevice->disconnectDevice();
    }
    kaiqi();
}

void plc::cut()
{
    modbusDevice->disconnectDevice();
    qDebug()<< "关闭plc";
}

//从服务器读数据的读按钮槽方法
void plc::kaishicaiji1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    //从寄存器地址0开始连续读取36个数
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters,0,36);
    qDebug()<<"plc采集36个数";
    if (auto *reply = modbusDevice->sendReadRequest(readUnit,1)) {
        if (!reply->isFinished())
        {
            qDebug()<<"plc连接了";
            emit xintiaoplc(2);
            connect(reply, &QModbusReply::finished, this, &plc::readReady1);
        }
        else
        {
            delete reply; // broadcast replies return immediately
        }
    }
    //    //从寄存器地址40开始连续读取1个数(心跳包）
    //    QModbusDataUnit readUnit2(QModbusDataUnit::HoldingRegisters,40,1);
    //    if (auto *reply2 = modbusDevice->sendReadRequest(readUnit2,1)) {
    //        if (!reply2->isFinished())
    //        {
    //            qDebug()<<"连接了";
    //            emit xintiao1(1);
    //        }
    //        else
    //        {
    //            qDebug()<<"断开连接了";
    //            emit xintiao2(2);
    //        }
    //            delete reply2; // broadcast replies return immediately
    //    }

}

//在这里读的数据
void plc::readReady1()
{
    //QModbusReply这个类存储了来自client的数据,sender()返回发送信号的对象的指针
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
    {
        return;
    }

    //数据从QModbusReply这个类的result方法中获取,也就是本程序中的reply->result()
    //判断是否出错
    const QModbusDataUnit unit = reply->result();

    //写入txt
    QFile file(file_PLC);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream dataStr(&file);


    QFile file2(file_PLC2);
    file2.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream dataStr2(&file2);
    uint16_t var1 = unit.value(0);
    dataStr<<QString::number(var1);
    dataStr2<<QString::number(var1);
    uint16_t var2 = unit.value(1);
    dataStr<<QString::number(var2);
    dataStr2<<QString::number(var2);
    uint16_t var3 = unit.value(2);
    dataStr<<QString::number(var3);
    dataStr2<<QString::number(var3);
    uint16_t var4 = unit.value(3);
    dataStr<<QString::number(var4);
    dataStr2<<QString::number(var4);
    uint16_t var5 = unit.value(4);
    dataStr<<QString::number(var5);
    dataStr2<<QString::number(var5);
    uint16_t var6 = unit.value(5);
    dataStr<<QString::number(var6);
    dataStr2<<QString::number(var6);
    uint16_t var7 = unit.value(6);
    dataStr<<QString::number(var7);
    dataStr2<<QString::number(var7);
    uint16_t var8 = unit.value(7);
    dataStr<<QString::number(var8);
    dataStr2<<QString::number(var8);
    uint16_t var9 = unit.value(8);
    dataStr<<QString::number(var9);
    dataStr2<<QString::number(var9);
    uint16_t var10 = unit.value(9);
    dataStr<<QString::number(var10);
    dataStr2<<QString::number(var10);
    uint16_t var11 = unit.value(10);
    dataStr<<QString::number(var11);
    dataStr2<<QString::number(var11);
    uint16_t var12 = unit.value(11);
    dataStr<<QString::number(var12);
    dataStr2<<QString::number(var12);
    uint16_t var13 = unit.value(12);
    dataStr<<QString::number(var13);
    dataStr2<<QString::number(var13);
    uint16_t var14 = unit.value(13);
    dataStr<<QString::number(var14);
    dataStr2<<QString::number(var14);
    uint16_t var15 = unit.value(14);
    dataStr<<QString::number(var15);
    dataStr2<<QString::number(var15);
    uint16_t var16 = unit.value(15);
    dataStr<<QString::number(var16);
    dataStr2<<QString::number(var16);
    uint16_t var17 = unit.value(16);
    dataStr<<QString::number(var17);
    dataStr2<<QString::number(var17);
    uint16_t var18 = unit.value(17);
    dataStr<<QString::number(var18);
    dataStr2<<QString::number(var18);
    uint16_t var19 = unit.value(18);
    dataStr<<QString::number(var19);
    dataStr2<<QString::number(var19);
    uint16_t var20 = unit.value(19);
    dataStr<<QString::number(var20);
    dataStr2<<QString::number(var20);
    uint16_t var21 = unit.value(20);
    dataStr<<QString::number(var21);
    dataStr2<<QString::number(var21);
    uint16_t var22 = unit.value(21);
    dataStr<<QString::number(var22);
    dataStr2<<QString::number(var22);
    uint16_t var23 = unit.value(22);
    dataStr<<QString::number(var23);
    dataStr2<<QString::number(var23);
    uint16_t var24 = unit.value(23);
    dataStr<<QString::number(var24);
    dataStr2<<QString::number(var24);
    uint16_t var25 = unit.value(24);
    dataStr<<QString::number(var25);
    dataStr2<<QString::number(var25);
    uint16_t var26 = unit.value(25);
    dataStr<<QString::number(var26);
    dataStr2<<QString::number(var26);
    uint16_t var27 = unit.value(26);
    dataStr<<QString::number(var27);
    dataStr2<<QString::number(var27);
    uint16_t var28 = unit.value(27);
    dataStr<<QString::number(var28);
    dataStr2<<QString::number(var28);
    uint16_t var29 = unit.value(28);
    dataStr<<QString::number(var29);
    dataStr2<<QString::number(var29);
    uint16_t var30 = unit.value(29);
    dataStr<<QString::number(var30);
    dataStr2<<QString::number(var30);
    uint16_t var31 = unit.value(30);
    dataStr<<QString::number(var31);
    dataStr2<<QString::number(var31);
    uint16_t var32 = unit.value(31);
    dataStr<<QString::number(var32);
    dataStr2<<QString::number(var32);
    uint16_t var33 = unit.value(32);
    dataStr<<QString::number(var33);
    dataStr2<<QString::number(var33);
    uint16_t var34 = unit.value(33);
    dataStr<<QString::number(var34);
    dataStr2<<QString::number(var34);
    uint16_t var35 = unit.value(34);
    dataStr<<QString::number(var35);
    dataStr2<<QString::number(var35);
    uint16_t var36 = unit.value(35);
    dataStr<<QString::number(var36);
    dataStr2<<QString::number(var36);

    file.close();
    file2.close();
    emit flush_modbus_value1();
    value2=value2+1;
    qDebug() << "value2为： " << value2;
    caozuodu();

}

void plc::write(int a,int b)//a为地址，b为写入的值
{
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, a, 1);
    writeData.setValue(0,b);
    qDebug() << "发送的数据为： " << writeData.values();
    QModbusReply* reply = modbusDevice->sendWriteRequest(writeData, 1);
    if (reply)
    {
        if (!reply->isFinished())
        {
            //接收响应信息
            connect(reply, &QModbusReply::finished, this, [this, reply](){
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    //接收到的响应信息是协议错误
                    qDebug() << "写入数据错误：" << reply->errorString();
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    //接收到的响应消息是其它错误
                    qDebug() << "写入数据错误： " << reply->errorString();
                }
                else
                {
                    //接收到的消息没有错误 一般没有必要解析响应消息
                    const QModbusDataUnit data = reply->result();

                    qDebug() << "消息数据个数：" << data.valueCount() << " :" << data.values();

                }

                reply->deleteLater();
            });
        }
        else
        {
            //发送没有响应数据
            //broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else
    {
        qDebug() << "sendWriteRequest Error: " << reply->errorString();
    }
}

void plc::rev1(int a)
{
    plc_kozhishu =a;
    qDebug() << "plc_kozhishu: " << plc_kozhishu;
    chonddian1();
    chonddian2();
    open1();
    open2();
    close1();
    close2();
    stop1();
    stop2();
    up1();
    up2();
    down1();
    down2();
    pause1();
    pause2();
}

void plc::chonddian1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==1)
    {
        write(21,1);
    }
    if(plc_kozhishu==2)
    {
        write(21,0);
    }
}

void plc::chonddian2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==15)
    {
        write(29,1);
    }
    if(plc_kozhishu==16)
    {
        write(29,0);
    }
}

void plc::open1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==3)
    {
        write(22,1);
    }
    if(plc_kozhishu==4)
    {
        write(22,0);
    }
}

void plc::open2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==17)
    {
        write(30,1);
    }
    if(plc_kozhishu==18)
    {
        write(30,0);
    }
}

void plc::close1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==5)
    {
        write(23,1);
    }
    if(plc_kozhishu==6)
    {
        write(23,0);
    }
}

void plc::close2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==19)
    {
        write(31,1);
    }
    if(plc_kozhishu==20)
    {
        write(31,0);
    }
}

void plc::stop1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==7)
    {
        write(24,1);
    }
    if(plc_kozhishu==8)
    {
        write(24,0);
    }
}

void plc::stop2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==21)
    {
        write(32,1);
    }
    if(plc_kozhishu==22)
    {
        write(32,0);
    }
}

void plc::up1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==9)
    {
        write(25,1);
    }
    if(plc_kozhishu==10)
    {
        write(25,0);
    }
}

void plc::up2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==23)
    {
        write(33,1);
    }
    if(plc_kozhishu==24)
    {
        write(33,0);
    }
}

void plc::down1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==11)
    {
        write(26,1);
    }
    if(plc_kozhishu==12)
    {
        write(26,0);
    }
}

void plc::down2()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==25)
    {
        write(34,1);
    }
    if(plc_kozhishu==26)
    {
        write(34,0);
    }
}

void plc::pause1()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==13)
    {
        write(27,1);
    }
    if(plc_kozhishu==14)
    {
        write(27,0);
    }
}

void plc::pause2()
{
    qDebug() << "plc_kozhishu1: " << plc_kozhishu;
    //如果设备没有被创建就返回
    if (!modbusDevice)
    {
        return;
    }
    if(plc_kozhishu==27)
    {
        qDebug() << "plc_kozhishu2: " << plc_kozhishu;
        write(35,1);
    }
    if(plc_kozhishu==28)
    {
        write(35,0);
    }

}

void plc::caozuodu()
{
    int value2_yu;
    value2_yu=value2 % 5;
    qDebug() << "value2_yu为： " << value2_yu;
    if (value2_yu==0)
    {
        qDebug() << "mmmmm ";
        emit flush_modbus_value2();
    }
}
