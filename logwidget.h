#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = nullptr);
    ~LogWidget();

    void form_init(); //格式初始化
    void func_init(); //功能初始化
    void message_init(QString flag1,QString flag2);

signals:
    void login(); //登录主界面信号
    void close_window();  //关闭登录界面信号

private slots:
    void on_btn_sure_clicked();//登录按钮按下后触发的事件
    void on_btn_off_clicked();//取消按钮按下后触发的事件

private:
    Ui::LogWidget *ui;

    QString m_password1;
    QString m_password2;
    QString m_password3;
};

#endif // LOGWIDGET_H
