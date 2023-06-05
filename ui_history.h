/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_history
{
public:
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_14;
    QTableWidget *tableWidget_2;
    QGroupBox *groupBox;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_4;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_5;
    QDateTimeEdit *dateTimeEdit_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QWidget *widget_2;
    QWidget *widget_4;
    QWidget *widget_6;

    void setupUi(QWidget *history)
    {
        if (history->objectName().isEmpty())
            history->setObjectName(QString::fromUtf8("history"));
        history->resize(1262, 662);
        gridLayout_15 = new QGridLayout(history);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        tableWidget_2 = new QTableWidget(history);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setMaximumSize(QSize(130, 7000000));

        gridLayout_14->addWidget(tableWidget_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(history);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 300));

        gridLayout_14->addWidget(groupBox, 0, 1, 1, 1);

        tableWidget = new QTableWidget(history);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMinimumSize(QSize(700, 50));
        tableWidget->setMaximumSize(QSize(16777215, 7000000));

        gridLayout_14->addWidget(tableWidget, 0, 2, 1, 1);

        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_4 = new QLabel(history);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(history);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setDateTime(QDateTime(QDate(2022, 7, 22), QTime(0, 0, 0)));
        dateTimeEdit->setDate(QDate(2022, 7, 22));
        dateTimeEdit->setCalendarPopup(true);

        gridLayout_4->addWidget(dateTimeEdit, 0, 1, 1, 1);

        label_5 = new QLabel(history);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 1, 0, 1, 1);

        dateTimeEdit_2 = new QDateTimeEdit(history);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
        dateTimeEdit_2->setDateTime(QDateTime(QDate(2022, 7, 22), QTime(17, 30, 0)));
        dateTimeEdit_2->setDate(QDate(2022, 7, 22));
        dateTimeEdit_2->setCalendarPopup(true);

        gridLayout_4->addWidget(dateTimeEdit_2, 1, 1, 1, 1);


        gridLayout_13->addLayout(gridLayout_4, 0, 0, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBox = new QCheckBox(history);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        checkBox_2 = new QCheckBox(history);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_2->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(history);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_2->addWidget(checkBox_3);

        checkBox_5 = new QCheckBox(history);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        horizontalLayout_2->addWidget(checkBox_5);


        gridLayout_13->addLayout(horizontalLayout_2, 1, 0, 1, 3);

        pushButton_3 = new QPushButton(history);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_13->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_2 = new QPushButton(history);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_13->addWidget(pushButton_2, 2, 1, 1, 1);

        pushButton_4 = new QPushButton(history);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_13->addWidget(pushButton_4, 2, 2, 1, 1);


        gridLayout_14->addLayout(gridLayout_13, 0, 3, 1, 1);


        gridLayout_15->addLayout(gridLayout_14, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(history);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(300, 212));

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(history);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(300, 0));

        gridLayout_3->addWidget(widget_2, 0, 1, 1, 1);

        widget_4 = new QWidget(history);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(300, 211));

        gridLayout_3->addWidget(widget_4, 1, 0, 1, 1);

        widget_6 = new QWidget(history);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));

        gridLayout_3->addWidget(widget_6, 1, 1, 1, 1);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 1);
        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);

        gridLayout_15->addLayout(gridLayout_3, 1, 0, 1, 1);

        gridLayout_15->setRowStretch(0, 1);
        gridLayout_15->setRowStretch(1, 5);

        retranslateUi(history);

        QMetaObject::connectSlotsByName(history);
    } // setupUi

    void retranslateUi(QWidget *history)
    {
        history->setWindowTitle(QCoreApplication::translate("history", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        groupBox->setTitle(QString());
        label_4->setText(QCoreApplication::translate("history", "\350\265\267\345\247\213\346\227\266\351\227\264", nullptr));
        label_5->setText(QCoreApplication::translate("history", "\347\273\210\346\255\242\346\227\266\351\227\264", nullptr));
        checkBox->setText(QCoreApplication::translate("history", "\350\241\250\346\240\274\344\270\200", nullptr));
        checkBox_2->setText(QCoreApplication::translate("history", "\350\241\250\346\240\274\344\272\214", nullptr));
        checkBox_3->setText(QCoreApplication::translate("history", "\350\241\250\346\240\274\344\270\211", nullptr));
        checkBox_5->setText(QCoreApplication::translate("history", "\350\241\250\346\240\274\345\233\233", nullptr));
        pushButton_3->setText(QCoreApplication::translate("history", " \346\230\276\347\244\272\346\211\200\346\234\211\346\225\260\346\215\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("history", "\346\230\276\347\244\272\345\233\276\350\241\250", nullptr));
        pushButton_4->setText(QCoreApplication::translate("history", "\344\277\235\345\255\230pdf\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class history: public Ui_history {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
