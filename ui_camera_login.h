/********************************************************************************
** Form generated from reading UI file 'camera_login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_LOGIN_H
#define UI_CAMERA_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_camera_login
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *frame_demo;

    void setupUi(QWidget *camera_login)
    {
        if (camera_login->objectName().isEmpty())
            camera_login->setObjectName(QString::fromUtf8("camera_login"));
        camera_login->resize(654, 208);
        gridLayout_2 = new QGridLayout(camera_login);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(camera_login);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(camera_login);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 2);

        label_2 = new QLabel(camera_login);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(camera_login);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 2);

        label_3 = new QLabel(camera_login);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(camera_login);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 2);

        label_4 = new QLabel(camera_login);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_4 = new QLineEdit(camera_login);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 3, 1, 1, 2);

        pushButton = new QPushButton(camera_login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 4, 1, 1, 1);

        pushButton_2 = new QPushButton(camera_login);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        frame_demo = new QFrame(camera_login);
        frame_demo->setObjectName(QString::fromUtf8("frame_demo"));
        frame_demo->setFrameShape(QFrame::StyledPanel);
        frame_demo->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(frame_demo, 0, 1, 1, 1);


        retranslateUi(camera_login);

        QMetaObject::connectSlotsByName(camera_login);
    } // setupUi

    void retranslateUi(QWidget *camera_login)
    {
        camera_login->setWindowTitle(QCoreApplication::translate("camera_login", "Form", nullptr));
        label->setText(QCoreApplication::translate("camera_login", "IP\345\234\260\345\235\200", nullptr));
        label_2->setText(QCoreApplication::translate("camera_login", "\347\253\257\345\217\243\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("camera_login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("camera_login", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("camera_login", "\347\231\273\345\275\225", nullptr));
        pushButton_2->setText(QCoreApplication::translate("camera_login", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class camera_login: public Ui_camera_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_LOGIN_H
