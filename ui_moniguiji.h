/********************************************************************************
** Form generated from reading UI file 'moniguiji.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONIGUIJI_H
#define UI_MONIGUIJI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_moniguiji
{
public:
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_7;

    void setupUi(QWidget *moniguiji)
    {
        if (moniguiji->objectName().isEmpty())
            moniguiji->setObjectName(QString::fromUtf8("moniguiji"));
        moniguiji->resize(769, 556);
        dockWidget = new QDockWidget(moniguiji);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setGeometry(QRect(0, 0, 231, 471));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_2 = new QLineEdit(dockWidgetContents);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        lineEdit_3 = new QLineEdit(dockWidgetContents);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        pushButton_2 = new QPushButton(dockWidgetContents);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 3);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        pushButton_6 = new QPushButton(dockWidgetContents);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 7, 0, 1, 3);

        pushButton_3 = new QPushButton(dockWidgetContents);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 8, 0, 1, 3);

        pushButton_4 = new QPushButton(dockWidgetContents);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 5, 0, 1, 3);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 6, 0, 1, 1);

        pushButton_5 = new QPushButton(dockWidgetContents);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 4, 0, 1, 3);

        lineEdit = new QLineEdit(dockWidgetContents);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 6, 1, 1, 2);

        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 3);

        pushButton_7 = new QPushButton(dockWidgetContents);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 3, 0, 1, 3);

        dockWidget->setWidget(dockWidgetContents);

        retranslateUi(moniguiji);

        QMetaObject::connectSlotsByName(moniguiji);
    } // setupUi

    void retranslateUi(QWidget *moniguiji)
    {
        moniguiji->setWindowTitle(QCoreApplication::translate("moniguiji", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("moniguiji", "\346\240\207\346\263\250\350\275\250\350\277\271\347\202\271", nullptr));
        label_2->setText(QCoreApplication::translate("moniguiji", "\345\275\223\345\211\215\347\202\271\347\232\204\345\235\220\346\240\207", nullptr));
        pushButton_6->setText(QCoreApplication::translate("moniguiji", "\344\277\235\345\255\230\345\233\276\347\211\207\350\207\263\344\270\273\347\252\227\345\217\243", nullptr));
        pushButton_3->setText(QCoreApplication::translate("moniguiji", "\350\247\204\345\210\222\345\256\214\346\210\220", nullptr));
        pushButton_4->setText(QCoreApplication::translate("moniguiji", "\350\275\250\350\277\271\350\277\236\347\272\277", nullptr));
        label->setText(QCoreApplication::translate("moniguiji", "\350\275\250\350\277\271\346\200\273\351\225\277\345\272\246", nullptr));
        pushButton_5->setText(QCoreApplication::translate("moniguiji", "\345\210\240\351\231\244\350\275\250\350\277\271\347\202\271", nullptr));
        pushButton->setText(QCoreApplication::translate("moniguiji", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        pushButton_7->setText(QCoreApplication::translate("moniguiji", "\344\277\256\346\224\271\345\235\220\346\240\207\347\202\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class moniguiji: public Ui_moniguiji {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONIGUIJI_H
