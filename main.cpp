#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include <QApplication>
#include "logwidget.h"
#include <QTextCodec>
#include <QPushButton>
#include <QDebug>
#include <QString>

////DbgHelp
#include <windows.h>
#include <DbgHelp.h>
#include <QDateTime>
#include <QMessageBox>

#include "qBreakpad/include/QBreakpadHandler.h"

//程序异常捕获
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    //初始化dump文件夹
    QString logFilePath = QCoreApplication::applicationDirPath() + "/DumpCrashes/";
    QDir dstDir(logFilePath);
    if(!dstDir.exists())
    {
        if(!dstDir.mkpath(logFilePath))
        {
            qDebug()<<__FILE__<<__LINE__<<"创建DumpCrashes文件夹失败！";
        }
    }

    //创建Dump文件
    QString dumpFileName = logFilePath + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".dmp";
    HANDLE hDumpFile = CreateFile((LPCWSTR)(dumpFileName.toStdWString().c_str()), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hDumpFile != INVALID_HANDLE_VALUE)
    {
        //Dump信息
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        //写入Dump文件内容
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, (MINIDUMP_TYPE)(MiniDumpWithDataSegs | MiniDumpWithProcessThreadData | MiniDumpWithUnloadedModules), &dumpInfo, NULL, NULL);
    }

    //这里弹出一个错误对话框并退出程序
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode,16));
    QString errAddr(QString::number((uint)record->ExceptionAddress,16));
    QMessageBox::critical(NULL,"错误",QString("程序异常崩溃捕获！\nerrCode：%1 \nerrAddr：%2").arg(errCode.toStdString().c_str()).arg(errAddr.toStdString().c_str()));

    return EXCEPTION_EXECUTE_HANDLER;
}

void outputMessage(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    //初始化log文件夹
    QString logFilePath = QCoreApplication::applicationDirPath() + "/DebugLog/";
    QDir dstDir(logFilePath);
    if(!dstDir.exists())
    {
        if(!dstDir.mkpath(logFilePath))
        {
            qDebug()<<__FILE__<<__LINE__<<"创建DebugLog文件夹失败！";
        }
    }

    //获取输出内容
    QString debugDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString debugMsg = QString("%1 \r\n%2").arg(debugDateTime).arg(msg);

    //保存文件
    QString logFileName = logFilePath + "log_" + QDate::currentDate().toString("yyyyMMdd") + ".txt";
    QFile file(logFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream << debugMsg << "\r\n \r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //生成输出日志
    qInstallMessageHandler(outputMessage);
    //注冊异常捕获函数
    QBreakpadInstance.setDumpPath("BreakCrashes");   //捕获构造时的异常
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);   //捕获构造时的异常


    a.setFont(QFont("Microsoft Yahei", 9));

    //设置中文编码
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    MainWindow w;
    QBreakpadInstance.setDumpPath("BreakCrashes");   //捕获构造完成之后的异常
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);   //捕获构造完成之后的异常

    return a.exec();
}
