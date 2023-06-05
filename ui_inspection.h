/********************************************************************************
** Form generated from reading UI file 'inspection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTION_H
#define UI_INSPECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_inspection
{
public:
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_8;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;

    void setupUi(QWidget *inspection)
    {
        if (inspection->objectName().isEmpty())
            inspection->setObjectName(QString::fromUtf8("inspection"));
        inspection->resize(997, 641);
        gridLayout_4 = new QGridLayout(inspection);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(328, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(inspection);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 11pt \"Agency FB\";"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(328, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 3);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(inspection);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(inspection);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(inspection);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(inspection);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 2, 1, 1);

        lineEdit = new QLineEdit(inspection);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        lineEdit_5 = new QLineEdit(inspection);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 4, 2, 1, 1);

        label_6 = new QLabel(inspection);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 1, 1, 1);

        label_5 = new QLabel(inspection);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 4, 1, 1, 1);

        lineEdit_4 = new QLineEdit(inspection);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 3, 2, 1, 1);

        lineEdit_3 = new QLineEdit(inspection);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(110, 0));

        gridLayout->addWidget(lineEdit_3, 2, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout_3, 1, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(327, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_8, 1, 1, 1, 1);

        frame = new QFrame(inspection);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(260, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(frame, 1, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_2 = new QPushButton(inspection);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 1, 1, 1, 1);

        tableWidget = new QTableWidget(inspection);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 2);

        pushButton = new QPushButton(inspection);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(inspection);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(inspection);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 2, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 2, 0, 1, 3);


        retranslateUi(inspection);

        QMetaObject::connectSlotsByName(inspection);
    } // setupUi

    void retranslateUi(QWidget *inspection)
    {
        inspection->setWindowTitle(QCoreApplication::translate("inspection", "\345\267\241\346\243\200", nullptr));
        label->setText(QCoreApplication::translate("inspection", "\345\267\241\346\243\200\344\273\273\345\212\241\351\205\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("inspection", "\345\267\241\346\243\200\347\202\271\350\267\235\347\246\273(/m)", nullptr));
        label_4->setText(QCoreApplication::translate("inspection", "\345\211\215\346\221\204\345\203\217\345\244\264y\350\256\276\345\256\232(0~180)", nullptr));
        label_3->setText(QCoreApplication::translate("inspection", "\345\211\215\346\221\204\345\203\217\345\244\264x\350\256\276\345\256\232(0~360)", nullptr));
        lineEdit_2->setText(QString());
        lineEdit->setText(QString());
        lineEdit_5->setText(QString());
        label_6->setText(QCoreApplication::translate("inspection", "\345\220\216\346\221\204\345\203\217\345\244\264y\350\256\276\345\256\232(0~180)", nullptr));
        label_5->setText(QCoreApplication::translate("inspection", "\345\220\216\346\221\204\345\203\217\345\244\264x\350\256\276\345\256\232(0~360)", nullptr));
        lineEdit_4->setText(QString());
        lineEdit_3->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("inspection", "\345\210\240\351\231\244\345\267\241\346\243\200\347\202\271", nullptr));
        pushButton->setText(QCoreApplication::translate("inspection", "\346\267\273\345\212\240\345\267\241\346\243\200\347\202\271", nullptr));
        pushButton_4->setText(QCoreApplication::translate("inspection", "\345\210\240\351\231\244\345\267\241\346\243\200\344\273\273\345\212\241", nullptr));
        pushButton_3->setText(QCoreApplication::translate("inspection", "\346\267\273\345\212\240\350\207\252\345\212\250\345\267\241\346\243\200\344\273\273\345\212\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inspection: public Ui_inspection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTION_H
