/********************************************************************************
** Form generated from reading UI file 'logwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWIDGET_H
#define UI_LOGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_pw;
    QLineEdit *edit_pw;
    QLabel *label_name;
    QComboBox *comboBox;
    QPushButton *btn_sure;
    QPushButton *btn_off;
    QFrame *frame_2;
    QLabel *label;

    void setupUi(QWidget *LogWidget)
    {
        if (LogWidget->objectName().isEmpty())
            LogWidget->setObjectName(QString::fromUtf8("LogWidget"));
        LogWidget->resize(852, 367);
        LogWidget->setStyleSheet(QString::fromUtf8("QGroupBox{border:none};"));
        horizontalLayout_2 = new QHBoxLayout(LogWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_2 = new QGroupBox(LogWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("border:none;"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frame = new QFrame(groupBox_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(frame, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        groupBox_3 = new QGroupBox(LogWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        groupBox_3->setFont(font);
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);\n"
"color:black;\n"
"font: 16px \"\351\273\221\344\275\223\";"));
        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(11, 110, 219, 77));
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8(""));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_pw = new QLabel(groupBox);
        label_pw->setObjectName(QString::fromUtf8("label_pw"));

        gridLayout->addWidget(label_pw, 2, 0, 1, 1);

        edit_pw = new QLineEdit(groupBox);
        edit_pw->setObjectName(QString::fromUtf8("edit_pw"));
        edit_pw->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(edit_pw, 2, 1, 1, 1);

        label_name = new QLabel(groupBox);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        gridLayout->addWidget(label_name, 1, 0, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);

        btn_sure = new QPushButton(groupBox_3);
        btn_sure->setObjectName(QString::fromUtf8("btn_sure"));
        btn_sure->setGeometry(QRect(11, 210, 80, 25));
        btn_off = new QPushButton(groupBox_3);
        btn_off->setObjectName(QString::fromUtf8("btn_off"));
        btn_off->setGeometry(QRect(209, 210, 80, 25));
        frame_2 = new QFrame(groupBox_3);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(11, 11, 389, 92));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 242, 80, 16));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(groupBox_3);


        retranslateUi(LogWidget);

        QMetaObject::connectSlotsByName(LogWidget);
    } // setupUi

    void retranslateUi(QWidget *LogWidget)
    {
        LogWidget->setWindowTitle(QCoreApplication::translate("LogWidget", "\350\275\250\351\201\223\346\234\272\345\231\250\344\272\272\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QString());
        label_pw->setText(QCoreApplication::translate("LogWidget", "\345\257\206\347\240\201", nullptr));
        edit_pw->setText(QCoreApplication::translate("LogWidget", "123", nullptr));
        label_name->setText(QCoreApplication::translate("LogWidget", "\347\224\250\346\210\267\345\220\215", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("LogWidget", "\347\224\250\346\210\2671", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("LogWidget", "\347\224\250\346\210\2672", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("LogWidget", "\347\224\250\346\210\2673", nullptr));

        btn_sure->setText(QCoreApplication::translate("LogWidget", "\347\241\256\350\256\244", nullptr));
        btn_off->setText(QCoreApplication::translate("LogWidget", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("LogWidget", "\345\222\214\345\270\206\346\234\272\345\231\250\344\272\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogWidget: public Ui_LogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWIDGET_H
