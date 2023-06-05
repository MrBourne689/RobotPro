#include "inspection.h"
#include "ui_inspection.h"


inspection::inspection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inspection)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowIcon(QIcon(":/images/icon.png"));
    #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    #if _MSC_VER
        QTextCodec *codec = QTextCodec::codecForName("GBK");
    #else
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    #endif
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
    #else
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
    #endif
    #if _MSC_VER >=1600

    #pragma execution_character_set("utf-8")
    #endif
        ui->tableWidget->setColumnCount(5);
        QStringList header;
        header<<"距离"<<"data_x1"<<"data_y1"<<"data_x2"<<"data_y2";
        QRegExp regexp_xunjianjuli("^[0-9]*[1-9][0-9]*$");
        QRegExpValidator *preg_xunjian = new QRegExpValidator(regexp_xunjianjuli, this);
        ui->lineEdit->setValidator(preg_xunjian);
        ui->tableWidget->setHorizontalHeaderLabels(header);
        ui->lineEdit->setValidator(preg_xunjian);
        QRegExp regexp_0To360("^([0-9]|[1-9]\\d|[1-2]\\d{0,2}|3[0-5]\\d|360)$");
        QRegExp regexp_0To180("^-?(180|1?[0-7]?\\d(\\.\\d{1,8})|[1-9]?\\d(\\.\\d{1,8})?)$");
        QRegExpValidator *pReg_180 = new QRegExpValidator(regexp_0To180, this);
        QRegExpValidator *pReg = new QRegExpValidator(regexp_0To360, this);
        ui->lineEdit_2->setValidator(pReg);
        ui->lineEdit_3->setValidator(pReg_180);
        ui->lineEdit_4->setValidator(pReg);
        ui->lineEdit_5->setValidator(pReg_180);
//        ui->frame->setStyleSheet("border-image: url(:/images/006.jpg);");
        ui->frame->setStyleSheet("border-image: url(:/images/ins.png);");
}

inspection::~inspection()
{
    delete ui;
}
void inspection::on_pushButton_clicked()
{
    int rowindex = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowindex);
    QString string1 = ui->lineEdit->text();
    QString string2 = ui->lineEdit_2->text();
    QString string3 = ui->lineEdit_3->text();
    QString string4 = ui->lineEdit_4->text();
    QString string5 = ui->lineEdit_5->text();
    if (string1!= "" && string2!= "" && string3!= "" && string4!= "" && string5!= "")
    {
        ui->tableWidget->setItem(rowindex,0,new QTableWidgetItem(string1));
        ui->tableWidget->setItem(rowindex,1,new QTableWidgetItem(string2));
        ui->tableWidget->setItem(rowindex,2,new QTableWidgetItem(string3));
        ui->tableWidget->setItem(rowindex,3,new QTableWidgetItem(string4));
        ui->tableWidget->setItem(rowindex,4,new QTableWidgetItem(string5));
    }
    else{
        QMessageBox::warning(this,"提示","请检查信息内容",QMessageBox::Ok);
    }

}

void inspection::on_pushButton_2_clicked()
{
    int rowindex = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(rowindex);
    QString filename = "data.txt";

}

void inspection::on_pushButton_3_clicked()
{
    QStringList data;
    bool kongzhi = 1;
    int allrow = ui->tableWidget->rowCount();
    if (allrow>0){
        for (int var = 0;var < allrow ;var++) {
            for (int i = 0; i < 5; ++i) {
                if (ui->tableWidget->item(var,i)->text() == ""){
                    QMessageBox::warning(this, "提示","请检查表格数据",QMessageBox::Ok);
                    kongzhi = 0;
                }
            }
            qDebug()<<ui->tableWidget->item(var,3)->text();
            data.append(QString("%1 %2 %3 %4 %5 %6 ").arg(QString("巡检点%1").arg(var+1)).arg(ui->tableWidget->item(var,0)->text()).arg(ui->tableWidget->item(var,1)->text()).arg(ui->tableWidget->item(var,2)->text()).arg(ui->tableWidget->item(var,3)->text()).arg(ui->tableWidget->item(var,4)->text()));
        }
    }
    if(kongzhi){
        qDebug()<<data;
        QString datapath = createfile(QString("任务%1").arg(QDateTime::currentDateTime().toString("Mhhmmss"))+".txt");
        path = datapath;
        qDebug()<<datapath;
        QFile file(datapath);
        if(file.open(QFile::WriteOnly|QIODevice::Text)){
            QTextStream s(&file);
            for (QString line : data) {
                s << line << "\n";

            }

    }
    }

}
QString inspection::createfile(QString filename){
    QDir tempdir;
    QString currerntDir = tempdir.currentPath();
    QString filepath = currerntDir + "/" + "points";
    if (!tempdir.exists(filepath)){
        qDebug()<<"不存在该路径"<<endl;
        tempdir.mkpath(filepath);
    }
    QFile *temfile = new QFile;
    tempdir.setCurrent(filepath);
    if (temfile->exists(filename)){
        qDebug()<<"文件存在";
        tempdir.setCurrent(currerntDir);
        emit send(filepath);
        qDebug()<<filepath;
        return (filepath + "/" + filename);
    }
    else {
        temfile->setFileName(filepath + "/" + filename);
    }
    if(!temfile->open(QIODevice::WriteOnly|QIODevice::Text)){
            QMessageBox::warning(this,"提示","未能成功创建文件夹",QMessageBox::Ok);
}
    temfile->close();
    tempdir.setCurrent(currerntDir);
    emit send(filepath);
    qDebug()<<filepath;
    return (filepath + "/" + filename);

}

void inspection::on_pushButton_4_clicked()
{

    QString path_remove = QFileDialog::getOpenFileName(this,"打开",path);
    if(path_remove==""){
        qDebug()<<"打开文件为空";

    }
    else {
        QFile::remove(path_remove);
    }

}


//void inspection::on_pushButton_5_clicked()
//{
//    bool kongzhi_0 = 1;
//    bool kongzhi_1 = 1;
//    int allow = ui->tableWidget->rowCount();
//    if(allow != 1)
//    {
//        QMessageBox::warning(this,"提示","请检查你的行数",QMessageBox::Ok);
//        kongzhi_0=1;
//    }
//    else {
//        if(kongzhi_0)
//        {
//            for (int i = 0; i < 5; ++i)
//            {

//                if (ui->tableWidget->item(0,i)->text() == "")
//                {
//                    QMessageBox::warning(this, "提示","请检查表格数据",QMessageBox::Ok);
//                    kongzhi_1 = 0;

//                }
//            }
//            if(kongzhi_1)
//               {

//                QStringList stringlist;
//                QString string = QString("%1 %2 %3 %4 %5 %6").arg("巡检点").arg(ui->tableWidget->item(0,0)->text()).arg(ui->tableWidget->item(0,1)->text()).arg(ui->tableWidget->item(0,2)->text()).arg(ui->tableWidget->item(0,3)->text()).arg(ui->tableWidget->item(0,4)->text());
//                stringlist.append(string);
//                qDebug()<<stringlist[0];
//                emit shoudongxunjian(stringlist);

//               }
//        }
//    }
//}

