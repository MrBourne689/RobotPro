#include "moniguiji.h"
#include "ui_moniguiji.h"
#include "QProcess"
#include "QString"
#include "QDebug"
#include "QFileDialog"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFont>
#include <QInputDialog>
#include <qtooltip.h>
#include<windows.h>
#include <synchapi.h>
#include <QScreen>
#include <QPixmap>
# pragma execution_character_set("utf-8")

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include <windows.h>

QImage image;
QString filename;
int p_a=0;//控制画笔
int S=0;//图中轨迹总长度
int L=0;//轨迹点总数量
int y_a=0;//控制点移动
int z,M;
double N;
int dingshiqi=0;
int weiyizhi;

QPoint P1, P2;//两个临时点
QPoint P[201];//点数组，防越界
QString Pl[201], pic;//每个点的标签，pic为当前背景图片的存储路径
int ways;//右侧显示栏路径的数量
double dis, min;//dis是搜索路径时路径长度当前值，min是路径长度最小值
bool showlen = false;//是否显示当前路径长度
struct lines { int a, b; bool f = false; } temp1, line[101];//线，ab是两点p1，p2的下标，f是否是最短路径，如是则标红，否则保持蓝色。temp1是当前线，line数组存储所有线
int count = 0;//添加的点的默认下标
class Stack//用于dfs，遍历时，“错误”路径时倒退
{
private:
    int a[101] = {};//存储点的下标
    int num = 0;//初始化点的个数
public:
    void push(int n) { a[++num] = n; }//压入栈
    void pop() { a[num--] = 0; }//出栈
    QString getstr()//右侧显示栏中点的标签展示，路径结果
    {
        QString str = "";
        for (int i = 1; i < num; i++)
            str += Pl[a[i]] + "->";
        str += Pl[a[num]];
        return str;
    }
    void showline()//将最短路径标红
    {
        for (int i = 1; i < num; i++)
        {
            for (int j = 1; line[j].a && j <= 100; j++)//在line[j]存在并且line数量在100以内循环
                if ((line[j].a == a[i] && line[j].b == a[i + 1]) || (line[j].b == a[i] && line[j].a == a[i + 1]))//如果线当中点的下标与最短路径栈中存储的点下标相同
                {
                    line[j].f = true;//标红
                    break;
                }
        }
    }
}stack, temp2;//temp2存储最短路径对应的栈
double moniguiji::dist(QPoint a, QPoint b)//计算两点间距离的函数
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
bool moniguiji::isin(QPoint x, QPoint y, int n)//判断鼠标光标是否点击成功（半径n的圆域范围内）
{
    if (dist(x, y) <= n) return true;
    else return false;
}

moniguiji::moniguiji(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::moniguiji)
{
    ui->setupUi(this);
    this->setWindowTitle("模拟轨迹管理系统");
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setFixedSize(1024,768);
    this->setStyleSheet("background-color:grey;");
    this->setWindowIcon(QIcon(":/images/icon.png"));
    ui->dockWidget->show();
    //按钮样式
    ui->dockWidgetContents->setStyleSheet("color:white;background-color:rgb(49, 49, 50);"
                                          );
    ui->pushButton->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->pushButton_2->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                    "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->pushButton_3->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                    "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->pushButton_4->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                    "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->pushButton_5->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                    "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->pushButton_6->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                    "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    ui->pushButton_7->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                    "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                    "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}");
    //创建数据库并连接
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("HeFanRobot");
        database.setPassword("123456");
    }
    //判断数据库连接
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug()<<"DataBase open sucess!";
    }
    //创建坐标表
    QSqlQuery sql_query;

    QString str_sql = "";

    str_sql = "create table zuobiao (id int primary key,x int,y int,s int)";
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"创建坐标表失败！！"<< sql_query.lastError();
    }
    else
    {
        qDebug()<<"创建坐标表成功";

    }
}

moniguiji::~moniguiji()
{
    delete ui;
}

void moniguiji::DFS(int i, int j)//i为起点，j为终点
{

}
void moniguiji::clr()//清除右侧显示栏的显示信息
{
    update();
}
void moniguiji::paintEvent(QPaintEvent*)//绘图函数
{
    if(p_a==1)
    {
        QPainter painter(this);//画笔，this为当前窗口
        //qDebug()<<filename;
        image.load(filename);
        //image.load("C:/Users/yuanxiaoping/OneDrive/桌面/91d05e98391052ff6db9403f47d29d6.png");
        //qDebug()<<image;
        QFont font1("Microsoft YaHei", 9);//字体说明
        QFont font2("Microsoft YaHei", 12);
        painter.drawImage(this->rect(),QImage(image));
        painter.setFont(font1);
        painter.setRenderHint(QPainter::Antialiasing, true);//使接下来的绘图光滑
        for (int i = 1; i <= num1; i++)
        {
            if (!line[i].f) painter.setPen(Qt::blue);//设置画笔颜色为蓝色
            else painter.setPen(Qt::red);
            painter.drawLine(P[line[i].a], P[line[i].b]);//两点连线
        }
        painter.setPen(Qt::darkMagenta);
        if (showlen)//如果显示路径
            for (int i = 1; i < num2; i++)
                for (int j = i + 1; j <= num2; j++)
                    if (matrix[i][j])//若路径存在
                    {
                        int x1, y1;
                        x1 = (P[i].x() + P[j].x()) / 2 - 10;//路径中央偏左
                        y1 = (P[i].y() + P[j].y()) / 2 + 4;//路径中央偏下
                        painter.drawText(QPoint(x1, y1), QString::number(matrix[i][j]));//路径长度显示在（x,y）位置处
                    }
        painter.setPen(Qt::black);
        painter.setBrush(Qt::yellow);
        painter.setFont(font2);
        for (int i = 1; i <= num2; i++)
        {
            painter.drawEllipse(P[i], 5, 5);//把点画出来
            painter.drawText(QPoint(P[i].x() + 5, P[i].y() + 6), Pl[i]);//画出点的标签，pl[i]为标签
        }
        if(z!=0)
        {
            qDebug()<<"动态点启动";
            dotai();
            painter.setPen(QPen(Qt::green,10));//设置画笔形式
            int A,B,C,D;
            QSqlQuery sql_query;
            QString str_sql1 = "";
            QString str_sql2 = "";
            QString str_sql3 = "";
            QString str_sql4 = "";
            qDebug()<<"M="<<M;
            str_sql1 = QString("select x from zuobiao where rowid = %1").arg(M);
            str_sql2 = QString("select x from zuobiao where rowid = %1").arg(M+1);
            str_sql3 = QString("select y from zuobiao where rowid = %1").arg(M);
            str_sql4 = QString("select y from zuobiao where rowid = %1").arg(M+1);
            if(!sql_query.exec(str_sql1))
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int a = sql_query.value(0).toDouble();
                    A=a;
                    qDebug()<<A;
                }
            }
            if(!sql_query.exec(str_sql2))
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int c = sql_query.value(0).toDouble();
                    C=c;
                    qDebug()<<C;
                }
            }
            if(!sql_query.exec(str_sql3))
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int b = sql_query.value(0).toDouble();
                    B=b;
                    qDebug()<<B;
                }
            }
            if(!sql_query.exec(str_sql4))
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    int d = sql_query.value(0).toDouble();
                    D=d;
                    qDebug()<<D;
                }
            }
            painter.drawPoint((C-A)*N+A,(D-B)*N+B);
            painter.setPen(QPen(Qt::blue,8));//设置画笔形式
        };
    }
}

void moniguiji::mousePressEvent(QMouseEvent* event)//功能实现
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint temp = event->pos();//event->pos为当前点击位置
        switch (tp)
        {
        case 1://选择第一个点
            if (num1 == 200) QMessageBox::warning(this, "警告", "路径数已达上限");
            else
                for (int i = 1; i <= num2-1; i++)
                {
                    P1 = P[i]; line[num1 + 1].a = i;//将第一个点信息存入P1，line[num1+1]，并开始case2功能
                    P2 = P[i+1]; line[num1 + 1].b = i+1;
                    int t=num1++;
                    //                        if (line[num1].a > line[num1].b)//保证线的第一个点下标比第二个小
                    //                        {
                    //                            int t1 = line[num1].a; line[num1].a = line[num1].b; line[num1].b = t1;
                    //                        }
                    if (t != num1)
                        matrix[line[num1].a][line[num1].b] = matrix[line[num1].b][line[num1].a] = dist(P[line[num1].a], P[line[num1].b]);
                } ;
            update(); break;
        case 2://选择第二个点
            //            for (int i = 1; i <= num2; i++)
            //                if (P[i] != P1 && isin(temp, P[i]))//若选中了与第一个点不同的点
            //                {
            //                    int t = num1++;//线数量+1
            //                    P2 = P[i]; line[num1].b = i; tp = 1;//P2信息录入，完善line[num1]信息（num1已+1），tp回归1.
            //                    if (line[num1].a > line[num1].b)//保证线的第一个点下标比第二个小
            //                    {
            //                        int t1 = line[num1].a; line[num1].a = line[num1].b; line[num1].b = t1;
            //                    }
            //                    for (int j = 1; j < num1; j++)//判断是否路线已经存在
            //                    {
            //                        if (line[num1].a == line[j].a && line[num1].b == line[j].b)
            //                        {
            //                            line[num1--] = line[0];
            //                            QMessageBox::warning(this, "警告", "两条路径重合");
            //                            break;
            //                        }
            //                    }
            //                    if (t != num1)//将两点间的像素距离赋值给两点间的路径长度（默认）
            //                        matrix[line[num1].a][line[num1].b] = matrix[line[num1].b][line[num1].a] = dist(P[line[num1].a], P[line[num1].b]);
            //                    break;
            //                }
            //            update(); break;
        case 3://添加点
            if (num2 < 100 && temp.x() >= 0 && temp.x() <=1024 /*image.width()*/&& temp.y()>0 && temp.y() <=768 /*image.height()*/)//判断所加的点是否在窗口范围内
            {
                int t = num2++;
                for (int i = 1; i < num2; i++)
                    if (isin(temp, P[i], 20))//判断两点是否太近，选中条件为“半径10的圆邻域”，故两点距离需要大于20
                    {
                        num2--; QMessageBox::warning(this, "警告", "两个点靠太近");
                    }
                if (t == num2) break;
                P[num2] = event->pos();//当前位置赋给最新的P点
                QString FxiugaiX= QString::number(P[num2].x());
                QString FxiugaiY= QString::number(P[num2].y());
                qDebug()<<"P[num2].X="<<P[num2].x();
                qDebug()<<"P[num2].Y="<<P[num2].y();
                ui->lineEdit_2->setText(FxiugaiX);
                ui->lineEdit_3->setText(FxiugaiY);
                int AxiugaiX=ui->lineEdit_2->text().toInt();
                int AxiugaiY=ui->lineEdit_3->text().toInt();
                P[num2].setX(AxiugaiX);
                P[num2].setY(AxiugaiY);
                qDebug()<<"P[num2].X="<<P[num2].x();
                qDebug()<<"P[num2].Y="<<P[num2].y();
                Pl[num2] = QString::number(++count);//创建默认标签
                update();
            }
            else if (num2 == 100) QMessageBox::warning(this, "警告", "点数已达上限");
            else QMessageBox::warning(this, "警告", "点超出边界");
            break;
        case 4://删除点
            if (num2 == 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//选中想要删除的点
                    {
                        for (int j = i; j < num2; j++)
                        {
                            P[j] = P[j + 1];//将删除的点后的点前移
                            Pl[j] = Pl[j+1];//点的标签同理
                            for (int k = 1; k <= num2; k++)//此一系列对matrix的操作使该点下标对应的行列删除
                                matrix[j][k] = matrix[j + 1][k];
                        }
                        for (int j = i; j < num2; j++)
                            for (int k = 1; k <= num2; k++)
                                matrix[k][j] = matrix[k][j + 1];
                        for (int j = 1; j <= num2; j++)
                            matrix[j][num2] = matrix[num2][j] = 0;
                        Pl[num2] = Pl[0];//最后一个点标签消失
                        P[num2--] = P[0];//最后一个点消失
                        for (int j = 1; j <= num1; j++)
                        {
                            if (i == line[j].a || i == line[j].b)//将line数组一并前移
                            {
                                for (int k = j; k < num1; k++)
                                    line[k] = line[k + 1];
                                line[num1--] = line[0];//将最后一条线消除，同时线数量减一
                                j--;
                            }
                            else//下标原在被选中的点之后的点所在线的下标前移
                            {
                                if (line[j].a > i) line[j].a--;
                                if (line[j].b > i) line[j].b--;
                            }
                        }

                        update();
                        break;
                    }
            break;
        case 5://选择第一个点删除路径
            if (num1 == 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//判断选中
                    {
                        P1 = P[i]; temp1.a = i; tp = 6;
                    } break;
        case 6://选择第二个点删除路径
            for (int i = 1; i <= num2; i++)
            {
                if (P[i] != P1 && isin(temp, P[i]))//选中
                {
                    P2 = P[i]; temp1.b = i; tp = 5;//第二个点信息载入
                    if (temp1.a > temp1.b)//保证线的第二个点下标大于第一个
                    {
                        int t1 = temp1.a; temp1.a = temp1.b; temp1.b = t1;
                    }
                    int t3 = num1;
                    for (int j = 1; j <= num1; j++)
                    {
                        if (temp1.a == line[j].a && temp1.b == line[j].b)
                        {
                            matrix[line[j].a][line[j].b] = matrix[line[j].b][line[j].a] = 0;//点之间路径长度删除
                            {for (int k = j; k < num1; k++)
                                    line[k] = line[k + 1];//路径（线）下标前移
                                line[num1--] = line[0];
                                break; }
                        }
                    }
                    if (num1 == t3) QMessageBox::warning(this, "警告", "找不到这条路径");
                    else break;
                }
            }
            update(); break;
        case 7://编辑点的标签
            if (num2 == 0) QMessageBox::warning(this, "警告", "无任何点");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))
                    {
                        QString s0 = QInputDialog::getText(this, "编辑标签", "输入文本(最多13个字)");
                        if (s0 != "") Pl[i] = s0.left(13);
                        break;
                    }
            break;
            //        case 8://选择起点
            //            for (int i = 1; i <= num2; i++)
            //                if (isin(temp, P[i]))
            //                {
            //                    P1 = P[i]; tp = 9;
            //                    temp1.a = i;//起点下标赋给temp1
            //                    ui->label->setText("起点：" + Pl[i]);
            //                    ui->label_2->setText("终点：");
            //                    break;
            //                } break;
            //        case 9://选择终点
            //            for (int i = 1; i <= num2; i++)
            //                if (P[i] != P1 && isin(temp, P[i]))//判断不与起点重合
            //                {
            //                    P2 = P[i];
            //                    temp1.b = i;//终点下标赋给temp1
            //                    ui->label_2->setText("终点：" + Pl[i]);
            //                    ways = 0;
            //                    min = 0;
            //                    DFS(temp1.a, temp1.b);
            //                    qDebug()<<ways;

            //                    if (ways)//若有路
            //                    {
            //                        qDebug("123456788");
            //                        if (ways > 200000) ;
            //                        else ui->label->setText(QString::number(min));
            //                        temp2.showline();//最短路径展示
            //                        qDebug("123456788");
            //                        update();
            //                    }
            //                    else /*ui->listWidget->addItem("找不到路径");*/
            //                    tp = 0;
            //                    break;
            //                }
            //            break;
        case 10://编辑路径长度第一个点
            if (num1 == 0) QMessageBox::warning(this, "警告", "无任何路径");
            else
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//选中
                    {
                        P1 = P[i]; tp = 11;//转入下一个case
                        temp1.a = i;
                        break;
                    } break;
        case 11://编辑路径长度第二个点
            for (int i = 1; i <= num2; i++)
                if (P[i] != P1 && isin(temp, P[i]))//不与第一个点重合
                {
                    P2 = P[i];
                    temp1.b = i;
                    tp = 10;
                    if (temp1.a > temp1.b)//保证线的第二个点下标大于第一个
                    {
                        int t1 = temp1.a; temp1.a = temp1.b; temp1.b = t1;
                    }
                    bool f0 = false;
                    for (int j = 1; j <= num1; j++)
                    {
                        if (temp1.a == line[j].a && temp1.b == line[j].b)
                        {
                            double number = QInputDialog::getDouble(this, "编辑长度", "输入浮点数(0.0001~999999)", matrix[temp1.a][temp1.b], 0.0001, 999999, 4);
                            if (number) matrix[temp1.a][temp1.b] = matrix[temp1.b][temp1.a] = number;//若输入了数，则点之间长度更改
                            f0 = true;
                            break;
                        }
                    }
                    if (!f0) QMessageBox::warning(this, "警告", "找不到这条路径");
                    update();
                    break;
                }
            break;
        }
    }
}

void moniguiji::mouseMoveEvent(QMouseEvent *event)
{
    int xiugaizuobiao=0;
    if(y_a==0)
    {
        if(event->buttons() == Qt::LeftButton)
        {
            //m=0;  //还应该在这在给m 赋一次值 为了清空鼠标上一次在某个点上留下的值
            QPoint temp = event->pos();//event->pos为当前点击位置
            //    QString zuo=QString("%1 %2").arg(event->pos().x()).arg(event->pos().y());
            //    QToolTip::showText(QPoint(event->globalPos()),zuo,this);  //显示鼠标坐标  更随鼠标用方框的形式
            //在mainwindows 这个类中用 mouseMoveEevent 事件只有点击拖动鼠标时才会有效 不知道是什么原因
            for(int i=0;i<5;i++){
                for (int i = 1; i <= num2; i++)
                    if (isin(temp, P[i]))//选中想要移动的点
                    {
                        xiugaizuobiao=i;
                        P[i]=event->pos();
                        update();
                    }
            }
        }
    }
}

void moniguiji::on_pushButton_clicked()
{
    filename=QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF *.webp )"));//可打开的文件类型
    //qDebug()<<filename;
    p_a=1;
}

void moniguiji::on_pushButton_2_clicked()
{
    clr();
    if (tp != 3) tp = 3;//转到case 3
    else tp = 0;//跳出
}

void moniguiji::on_pushButton_4_clicked()
{
    clr();
    if (tp != 1) tp = 1;//转到case 3
    else tp = 0;//跳出
}

void moniguiji::on_pushButton_3_clicked()
{
    on_pushButton_4_clicked();
    if (!showlen) showlen = true; /*ui->pushButton_6->setText("隐藏路径长");*/
    else showlen = false;
    update();
    clr();
    if (tp != 10) tp = 10;//转到case 10
    else tp = 0;//跳出
    qDebug()<<3;
    y_a=1;
    //将坐标点加入数据库
    QSqlQuery sql_query;
    QString str_sql = "";
    QString str_sql1 = "";
    //插入数据
    str_sql1 = QString("insert into zuobiao values('%1','%2','%3','%4')").arg(1).arg(P[1].x()).arg(P[1].y()).arg(weiyizhi);
    if(!sql_query.exec(str_sql1))
    {
        qDebug()<<"插入数据1失败！！"<< sql_query.lastError();
    }
    else
    {
        qDebug()<<"插入数据1成功";
    }

    for (int i=2;i<=num2;i++)
    {
        str_sql = QString("insert into zuobiao values('%1','%2','%3','%4')").arg(i).arg(P[i].x()).arg(P[i].y()).arg(matrix[line[i-1].a][line[i-1].b]);
        if(!sql_query.exec(str_sql))
        {
            qDebug()<<"插入数据1失败！！"<< sql_query.lastError();
        }
        else
        {
            qDebug()<<"插入数据1成功";
        }
    }
    m_timer.setInterval(1000);
    m_timer.start();
    qDebug()<<"我是定时器启动";
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
}

void moniguiji::on_pushButton_5_clicked()
{
    clr();
    if (tp != 4) tp = 4;//转到case 4
    else tp = 0;//跳出
}

void moniguiji::dotai()
{
    QSqlQuery sql_query;
    QString str_sql = "";
    QString select_sql1= "select sum(s) from zuobiao";
    QString select_max_sql = "select max(id) from zuobiao";
    if(!sql_query.exec(select_sql1))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            double s = sql_query.value(0).toDouble();
            S=s;
            qDebug()<<S;
        }
    }
    if(!sql_query.exec(select_max_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            double l = sql_query.value(0).toDouble();
            L=l;
            qDebug()<<L;
        }
    }
    double m,n,y,p;//m为轨迹总长度，n为动态点至起点在图中的轨迹长度
    int x;
    y=0;
    m = ui->lineEdit->text().toDouble();
    S=S-m;
    n=(S*z)/m;
    for(x=1;x<=L-1;x++)//不断计算一条线、两条线、三条线的长度，然后比较与n的大小，大于n时说明动态点在x条线内，然后计算点在第x条线的比例
    {
        double Ls;
        str_sql = QString("select s from zuobiao where rowid = %1").arg(x+1);
        if(!sql_query.exec(str_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                double ls = sql_query.value(0).toDouble();
                Ls=ls;
                qDebug()<<Ls;
            }
        }
        y=y+Ls;
        if(y>=n)
        {
            M=x;
            qDebug()<<M;
            p=y-Ls;
            qDebug()<<p;
            qDebug()<<(n-p);
            qDebug()<<(y-p);
            double yxp;//比例
            yxp=(n-p)/(y-p);
            qDebug()<<yxp;
            N=(n-p)/(y-p);
            break;
        }
    }

}

void moniguiji::on_pushButton_6_clicked()
{
    weiyizhi=ui->lineEdit->text().toDouble();
    emit send(weiyizhi);
    QSqlQuery sql_query;
    QString str_sql = "";

    //删除全部数据
    str_sql = QString("delete from zuobiao");
    //qDebug()<<str_sql;//控制台上打印拼接好的字符串
    if(!sql_query.exec(str_sql))
    {
        qDebug()<<"删除数据失败！！";
    }
    else
    {
        qDebug()<<"删除数据成功";
    }

    ui->dockWidget->close();
    QPixmap pixmap(this->size());
    render(&pixmap);
    //pixmap.save(QCoreApplication::applicationDirPath() + "/path.jpg");
    pixmap.save("./path.jpg");
    qDebug()<<"保存JPG";
    emit flush_path();//更新表格图片
    ui->dockWidget->show();
    //this->close();
}

void moniguiji::handleTimeout()
{
    int id;
    QSqlQuery sql_query;
    QString select_max_sql1 = "";
    QString select_max_sql = "select max(id) from student";
    if(!sql_query.exec(select_max_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            double l = sql_query.value(0).toDouble();
            id=l;
            qDebug()<<id;
        }
    }
    select_max_sql1 = QString("select xvalue from student where id = %1").arg(id);
    if(!sql_query.exec(select_max_sql1))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            double s = sql_query.value(0).toDouble();
            z=s;
            qDebug()<<"z="<<z;
        }
    }
    qDebug()<<z;
    update();
}

void moniguiji::on_pushButton_7_clicked()
{
    clr();
    int AxiugaiX=ui->lineEdit_2->text().toInt();
    int AxiugaiY=ui->lineEdit_3->text().toInt();
    P[num2].setX(AxiugaiX);
    P[num2].setY(AxiugaiY);
    qDebug()<<"P[num2].X="<<P[num2].x();
    qDebug()<<"P[num2].Y="<<P[num2].y();

}
