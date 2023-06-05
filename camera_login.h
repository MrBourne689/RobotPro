#ifndef CAMERA_LOGIN_H
#define CAMERA_LOGIN_H
#define file_name "camera.txt"
#define file_name2 "camera2.txt"
#include <QWidget>
#include <QDataStream>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
//相机
#include "avglobal.h"
#include "dhconfigsdk.h"
#include "dhnetsdk.h"

extern QString IP;
extern QString Port;
extern QString Name;
extern QString Password;

namespace Ui {
class camera_login;
}

class camera_login : public QWidget
{
    Q_OBJECT

signals:
    //自定义信号，当添加完成后，更新主界面上的表格
    void closeBox();
    //返回登录句柄
    void returnCan(LLONG);
public slots:
    //将新的信息写入到文件中
    void saveMessage();

public:
    explicit camera_login(QWidget *parent = nullptr);
    ~camera_login();

    void property();
    //相机
    void SDK();
    void moninit();
    void log1();
    void cut1();
    void next1();
    void log2();
    void cut2();
    void next2();
    static void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
    static void CALLBACK fRealDataCB(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param,LDWORD dwUser);
    static void CALLBACK HaveReConnect(LLONG lLoginID,char *pchDVRIP,LONG nDVRPort,LDWORD dwUser);

    //发出 closeBox 信号
    void emitCloseBox();

private:
    Ui::camera_login *ui;
    //相机
    char D_Ip[32] ={0};
    char D_UserName[32] = {0};
    char D_Pasdwd[32] = {0};
    int D_Port = 37777;
    int nIndex = 0;
    int a;
};

#endif // CAMERA_LOGIN_H
