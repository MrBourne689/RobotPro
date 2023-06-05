#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    //form_init();
    ui->groupBox_2->setStyleSheet("border-image: url(:/images/001.jpg);border:2px groove gray;border-radius:20px;");
    ui->frame_2->setStyleSheet("border-image: url(:/images/006.jpg);");
    this->setWindowIcon(QIcon(":/images/icon.png"));
    func_init();
}

LogWidget::~LogWidget()
{
    delete ui;
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(print_s()));
}

void LogWidget::form_init()
{
    // 文件标题名
    //ui->label_title->setGeometry(120,25,160,25);
    ui->groupBox->setGeometry(50,60,300,125);
    ui->label_name->setGeometry(25,25,100,25);
    ui->comboBox->setGeometry(125,25,150,25);
    ui->label_pw->setGeometry(25,75,100,25);
    ui->edit_pw->setGeometry(125,75,150,25);
    ui->btn_sure->setGeometry(50,235,120,30);
    ui->btn_off->setGeometry(230,235,120,30);


    //调整字体大小
    QFont font;
    font.setPointSize(16); //实际上是16的字号，但设成16却不行
    font.setFamily(("wenquanyi"));
    font.setBold(false);
    //ui->label_title->setFont(font);
    font.setPointSize(12);
    ui->label_name->setFont(font);
    ui->label_pw->setFont(font);
}
void LogWidget::func_init()
{
    // connect
    // 触发重置按钮的信号槽连接
    //connect(ui->btn_off,SIGNAL(clicked()),this,SLOT(on_btn_off_clicked()));
    // 触发登录按钮的信号槽连接
    //connect(ui->btn_sure,SIGNAL(clicked()),this,SLOT(on_btn_sure_clicked()));
    // 发出信号后关闭登录窗口的信号槽连接
    connect(this,SIGNAL(close_window()),this,SLOT(close()));
    //按钮及输入框样式
    ui->comboBox->setStyleSheet("border :  1px  solid  gray ;border-radius:  3px ;Font: 16px;background-color: white;"
                                );
    ui->groupBox_3->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;padding:3px 4px;border-style: outset;}"
                                  "QPushButton:hover{background-color:rgb(20, 22, 38); color: #bfe0ed;}"
                                  "QPushButton:pressed{background-color:grey;color: white;border-style: inset;}"

                                  "QComboBox::drop-down:hover,QComboBox::drop-down:pressed {background:grey;}"
                                  "QComboBox::drop-down{border-image: url(:/images/down.png);}"
                                  );
    ui->edit_pw->setStyleSheet("border :  1px  solid  gray ;border-radius:  3px ;background-color: rgb(240, 240, 240);");
    ui->edit_pw->setEchoMode(QLineEdit::Password);//输入的时候就显示圆点
    //创建网格布局控件
    QGridLayout *layout = new QGridLayout;
    //向 layout 中添加控件，并指定各个控件的位置
    layout->addWidget(ui->frame_2, 0, 0, 3, 2);
    layout->addWidget(ui->groupBox, 4, 0, 4, 2);
    layout->addWidget(ui->btn_sure, 9, 0);
    layout->addWidget(ui->btn_off, 9, 1);
    layout->addWidget(ui->label, 10, 0, 1, 2);
    ui->label->setStyleSheet("color:#1e69af");
    //将 layout 添加到 groupBox_3 窗口中
    ui->groupBox_3->setLayout(layout);
    //三个用户对应的密码
    m_password1 = "123";
    m_password2 = "456";
    m_password3 = "789";

}

void LogWidget::on_btn_off_clicked()
{
    ui->edit_pw->clear();
}

void LogWidget::on_btn_sure_clicked()
{
    QString password = ui->edit_pw->text();

    if ((ui->comboBox->currentIndex()==0 && password == m_password1)||(ui->comboBox->currentIndex()==1 && password == m_password2)||(ui->comboBox->currentIndex()==2 && password == m_password3))
    {
        emit(login());
        emit(close_window());
    }
    else
        QMessageBox::information(this, "Warning",QStringLiteral("密码错误 !"));
}












