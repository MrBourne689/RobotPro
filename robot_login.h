#ifndef ROBOT_LOGIN_H
#define ROBOT_LOGIN_H
#define file_robot "robot.txt"

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QModbusDataUnit> //存储接收和发送数据的类，数据类型为1bit和16bit
#include <QModbusReply> //客户端访问服务器后得到的回复（如客户端读服务器数据时包含数据信息）
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

namespace Ui {
class robot_login;
}

class robot_login : public QWidget
{
    Q_OBJECT
signals:
    //发出更新信号
    void flush_modbus();
public:
    explicit robot_login(QWidget *parent = nullptr);
    ~robot_login();
private slots:
    void on_lianjie_caijiqi_clicked();
    void on_kaiqi_caijiqi_clicked();
    void readReady();
    void kaishicaiji();

    void on_kaiqi_caijiqi_2_clicked();

    void on_kaiqi_caijiqi_3_clicked();

    void on_kaiqi_caijiqi_5_clicked();

    void on_kaiqi_caijiqi_6_clicked();

    void on_kaiqi_caijiqi_4_clicked();

    void on_kaiqi_caijiqi_7_clicked();
private:
    Ui::robot_login *ui;
    QModbusClient *modbusDevice = nullptr;
};

#endif // ROBOT_LOGIN_H
