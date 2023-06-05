#ifndef PDF_PAGE_H
#define PDF_PAGE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QtPrintSupport/QtPrintSupport>
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTime>
#include <windows.h>

namespace Ui {
class pdf_page;
}

class pdf_page : public QWidget
{
    Q_OBJECT

public:
    explicit pdf_page(QWidget *parent = nullptr);
    ~pdf_page();

    void initChart_p1();
    void initChart_p2();
    void initChart_p3();
    void initChart_p4();
    void initChart_p5();

private:
    Ui::pdf_page *ui;
};

#endif // PDF_PAGE_H
