#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QDataStream>
#include <camera_login.h>
#include <QHeaderView>
namespace Ui {
class camera;
}

class camera : public QWidget
{
    Q_OBJECT
public:
    explicit camera(QWidget *parent = nullptr);
    ~camera();

    void flushlistWidget(int row);
    void flushTable();
    void camera_in();

private:
    Ui::camera *ui;
    camera_login *cam_in;
};

#endif // CAMERA_H
