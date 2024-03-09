#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QMessageBox>
#include<QString>
#include<QDir>
#include<QTextEdit>
#include<QLineEdit>
#include<QPushButton>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QFile>
#include<QThread>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void SerialPortInit();//串口初始化（参数配置）
    ~MainWindow();

private:

    QSerialPort     *serial;// 定义全局的串口对象
    QStringList     baudList;//波特率
    QStringList     parityList;//校验位
    QStringList     dataBitsList;//数据位
    QStringList     stopBitsList;//停止位
    QStringList     flowControlList;//控制流

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
