#ifndef INSPECTION_H
#define INSPECTION_H

#include <QMainWindow>
#include <QTextCodec>
#include <QString>
#include <QtDebug>
#include <QTabWidget>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class inspection; }
QT_END_NAMESPACE
class inspection : public QWidget
{
    Q_OBJECT

public:
    inspection(QWidget *parent = nullptr);
    QString createfile(QString filename);
    ~inspection();
signals:
    void send(QString path);
    void shoudongxunjian(QStringList);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    QString path;

private:
    Ui::inspection *ui;
};

#endif // INSPECTION_H
