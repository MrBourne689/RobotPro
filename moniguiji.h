#ifndef MONIGUIJI_H
#define MONIGUIJI_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class moniguiji;
}

class moniguiji : public QWidget
{
    Q_OBJECT

public:
    explicit moniguiji(QWidget *parent = nullptr);
    int tp = 0;
    int num1 = 0, num2 = 0;//num1:线的数量、num2:点的数量
    double matrix[201][201] = {};
    bool reach[201] = {};
    void DFS(int P1, int P2);
    bool isin(QPoint x, QPoint y, int n = 10);
    double dist(QPoint a, QPoint b);
    void clr();
    ~moniguiji();

private slots:

    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent *event);//鼠标移动事件

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void dotai();

    void on_pushButton_6_clicked();

    void handleTimeout();
    void on_pushButton_7_clicked();

signals:
    void flush_path();
    void send(int);

private:
    Ui::moniguiji *ui;
    QTimer m_timer;
};

#endif // MONIGUIJI_H
