#include "robot_login.h"
#include "ui_robot_login.h"
#include <QModbusTcpClient>
#include <QDebug>
#include <QTime>
# pragma execution_character_set("utf-8")
double_t wendu1;
double_t wendu2;
double_t wendu3;
double_t wendu4;
double_t wendu5;
double_t wendu6;
double_t wendu7;
double_t wendu8;

robot_login::robot_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::robot_login)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    //主窗口背景颜色及字体颜色
    this->setStyleSheet("color:#0bbdc2;background-color:#141626");
    this->setWindowIcon(QIcon(":/images/icon.png"));
    //按钮样式
    ui->groupBox->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->groupBox_2->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->groupBox_3->setStyleSheet("QPushButton{color:#0bbdc2;background-color: rgb(42, 59, 81);border:2px groove gray;border-radius:10px;padding:2px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    //创建QModbusDevice对象
    modbusDevice = new QModbusTcpClient(this);
}

robot_login::~robot_login()
{
    delete ui;
}
void robot_login::on_kaiqi_caijiqi_clicked()
{
    kaishicaiji();
    QTimer *timer = new QTimer(this); //this 为parent类, 表示当前窗口
    connect(timer, SIGNAL(timeout()), this, SLOT(kaishicaiji())); // SLOT填入一个槽函数
    timer->start(1000); // 1000毫秒, 等于 1 秒
}

void robot_login::on_lianjie_caijiqi_clicked()
{
    if (!modbusDevice)
        return;
    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        //处于非连接状态，进行连接
        //TCP连接,端口502，地址127.0.0.1   192.168.2.100
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "192.168.2.100");
        //连接超时设置，2000ms
        qDebug("10");
        modbusDevice->setTimeout(2000);
        //连接失败重试连接，3次
        modbusDevice->setNumberOfRetries(3);
        //调试窗口显示连接状态
        if (modbusDevice->connectDevice()) {
            qDebug()<< "Connected!";
        }
    }
    else {
        //处在连接状态进行断开连接的操作
        modbusDevice->disconnectDevice();
    }
}

//从服务器读数据的读按钮槽方法
void robot_login::kaishicaiji()
{
    //如果设备没有被创建就返回
    if (!modbusDevice)
        return;
    //从寄存器地址32开始连续读取8个数
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters,0,8);
    if (auto *reply = modbusDevice->sendReadRequest(readUnit,1)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &robot_login::readReady);
        else
            delete reply; // broadcast replies return immediately
    }
}

//在这里读的数据
void robot_login::readReady()
{
    //QModbusReply这个类存储了来自client的数据,sender()返回发送信号的对象的指针
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;
    //数据从QModbusReply这个类的result方法中获取,也就是本程序中的reply->result()
    //判断是否出错
    qDebug()<<"currentTime--"<<QTime::currentTime().toString(Qt::ISODate);
    //qDebug() << wendu1;
    //    if (reply->error() == QModbusDevice::NoError) {
    //读取响应数据
    const QModbusDataUnit unit = reply->result();
    //qDebug() << unit.value(0);
    wendu1 = unit.value(0);
    wendu2 = unit.value(1);
    wendu3 = unit.value(2);
    wendu4 = unit.value(3);
    wendu5 = unit.value(4);
    wendu6 = unit.value(5);
    wendu7 = unit.value(6);
    wendu8 = unit.value(7);
//    qDebug("wendu1=%g", wendu1);
//    qDebug("wendu2=%g", wendu2);
//    qDebug("wendu3=%g", wendu3);
//    qDebug("wendu4=%g", wendu4);
//    qDebug("wendu5=%g", wendu5);
//    qDebug("wendu6=%g", wendu6);
//    qDebug("wendu7=%g", wendu7);
//    qDebug("wendu8=%g", wendu8);
    QFile file(file_robot);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QDataStream dataStr(&file);
    dataStr<<QString::number(wendu1)<<QString::number(wendu2)
           <<QString::number(wendu3)<<QString::number(wendu4)
           <<QString::number(wendu5)<<QString::number(wendu6)
           <<QString::number(wendu7)<<QString::number(wendu8);
    file.close();

    ui->wendu_1->setNum(wendu1);
    ui->wendu_2->setNum(wendu2);
    ui->wendu_3->setNum(wendu3);
    ui->wendu_4->setNum(wendu4);
    ui->wendu_5->setNum(wendu5);
    ui->wendu_6->setNum(wendu6);
    ui->wendu_7->setNum(wendu7);
    ui->wendu_8->setNum(wendu8);
    //发出更新信号
    emit flush_modbus();
    //    }
    //    qDebug("wendu1");
    //    reply->deleteLater();//删除reply
}
/*-----------06功能码------------*/
//前灯上电
void robot_login::on_kaiqi_caijiqi_2_clicked()
{
    //从地址104开始写1个寄存器的值
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 104, 1);
    writeData.setValue(0,16);
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
//后灯上电
void robot_login::on_kaiqi_caijiqi_3_clicked()
{
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 104, 1);
    writeData.setValue(0,32);
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

//摄像头上电
void robot_login::on_kaiqi_caijiqi_5_clicked()
{
    //从地址104开始写1个寄存器的值
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 104, 1);
    writeData.setValue(0,128);
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

//一键上电
void robot_login::on_kaiqi_caijiqi_6_clicked()
{
    //从地址104开始写1个寄存器的值
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 104, 1);
    writeData.setValue(0,4096);
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

//电机上电
void robot_login::on_kaiqi_caijiqi_4_clicked()
{
    //从地址104开始写1个寄存器的值
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 104, 1);
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
void robot_login::on_kaiqi_caijiqi_7_clicked()
{
    //传递电机转速
    QModbusDataUnit writeData(QModbusDataUnit::HoldingRegisters, 100, 1);
    writeData.setValue(0,50);
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
