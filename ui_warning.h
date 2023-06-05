/********************************************************************************
** Form generated from reading UI file 'warning.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARNING_H
#define UI_WARNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_warning
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton_3;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_17;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_18;
    QVBoxLayout *verticalLayout;
    QLabel *label_13;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_12;

    void setupUi(QWidget *warning)
    {
        if (warning->objectName().isEmpty())
            warning->setObjectName(QString::fromUtf8("warning"));
        warning->resize(1036, 651);
        gridLayout_2 = new QGridLayout(warning);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidget_2 = new QTableWidget(warning);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setMaximumSize(QSize(130, 16777215));

        gridLayout_2->addWidget(tableWidget_2, 3, 0, 1, 1);

        tableWidget = new QTableWidget(warning);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 8)
            tableWidget->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem12);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tableWidget, 3, 1, 1, 1);

        pushButton_3 = new QPushButton(warning);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 1, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(warning);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(warning);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(warning);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_3 = new QLineEdit(warning);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_3);

        lineEdit_5 = new QLineEdit(warning);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_5);

        lineEdit_7 = new QLineEdit(warning);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_7);

        lineEdit_9 = new QLineEdit(warning);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_9);

        lineEdit_11 = new QLineEdit(warning);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_11);

        lineEdit_13 = new QLineEdit(warning);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_13);

        lineEdit_15 = new QLineEdit(warning);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        lineEdit_15->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_15);

        lineEdit_17 = new QLineEdit(warning);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        lineEdit_17->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lineEdit_17);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(warning);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(warning);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_2);

        lineEdit_4 = new QLineEdit(warning);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_4);

        lineEdit_6 = new QLineEdit(warning);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_6);

        lineEdit_8 = new QLineEdit(warning);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_8);

        lineEdit_10 = new QLineEdit(warning);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_10);

        lineEdit_12 = new QLineEdit(warning);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_12);

        lineEdit_14 = new QLineEdit(warning);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        lineEdit_14->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_14);

        lineEdit_16 = new QLineEdit(warning);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        lineEdit_16->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_16);

        lineEdit_18 = new QLineEdit(warning);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));
        lineEdit_18->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineEdit_18);


        gridLayout->addLayout(verticalLayout_3, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_13 = new QLabel(warning);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_13);

        label_3 = new QLabel(warning);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(warning);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        label_6 = new QLabel(warning);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_6);

        label_5 = new QLabel(warning);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_5);

        label_8 = new QLabel(warning);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_8);

        label_7 = new QLabel(warning);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        label_10 = new QLabel(warning);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_10);

        label_9 = new QLabel(warning);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_9);

        label_12 = new QLabel(warning);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_12);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);


        retranslateUi(warning);

        QMetaObject::connectSlotsByName(warning);
    } // setupUi

    void retranslateUi(QWidget *warning)
    {
        warning->setWindowTitle(QCoreApplication::translate("warning", "\346\212\245\350\255\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("warning", "\345\217\230\351\207\217\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("warning", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("warning", "\346\225\260\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("warning", "\344\270\212\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("warning", "\344\270\213\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("warning", "\346\226\260\345\273\272\350\241\214", nullptr));
        pushButton_3->setText(QCoreApplication::translate("warning", "\345\205\250\351\203\250\346\225\260\346\215\256", nullptr));
        pushButton->setText(QCoreApplication::translate("warning", "\350\256\276\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("warning", "\344\270\213\351\231\220", nullptr));
        label_2->setText(QCoreApplication::translate("warning", "\344\270\212\351\231\220", nullptr));
        label_13->setText(QCoreApplication::translate("warning", "\351\230\210\345\200\274\350\256\276\345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("warning", "\346\234\272\345\231\250\344\272\272\350\277\220\350\241\214\351\200\237\345\272\246", nullptr));
        label_4->setText(QCoreApplication::translate("warning", "\347\224\265\346\261\240\347\224\265\345\216\213", nullptr));
        label_6->setText(QCoreApplication::translate("warning", "\346\234\272\345\231\250\344\272\272\350\205\224\344\275\223\346\270\251\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("warning", "CH4\346\265\223\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("warning", "O2\346\265\223\345\272\246", nullptr));
        label_7->setText(QCoreApplication::translate("warning", "H2S\346\265\223\345\272\246", nullptr));
        label_10->setText(QCoreApplication::translate("warning", "NH3\346\265\223\345\272\246", nullptr));
        label_9->setText(QCoreApplication::translate("warning", "\347\216\260\345\234\272\346\270\251\345\272\246", nullptr));
        label_12->setText(QCoreApplication::translate("warning", "\347\216\260\345\234\272\346\271\277\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class warning: public Ui_warning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARNING_H
