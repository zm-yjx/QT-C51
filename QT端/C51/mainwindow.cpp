#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(400,475);
    this->setWindowTitle("农场温度检测系统");
    this->show();
    connect(this->ui->but1,&QPushButton::clicked,this->ui->text,[=](){

       QString data=this->ui->text->toPlainText();
       QFile file("C:/Users/33746/Desktop/data.txt");//打开存放有搜索内容文本文件
       file.open(QIODevice::WriteOnly | QIODevice::Text);//采取写模式实现往搜索内容文档中写入内容

       QTextStream out(&file);
       out<<data;
       file.close();//写入数据

       QFile file1("C:/Users/33746/Desktop/low.txt");
       file1.open(QIODevice::ReadOnly | QIODevice::Text);//采取读模式实现只读取低温数据文档中的文本
       QTextStream in(&file1);
       QString line;
       while(!in.atEnd())
       {
           line=in.readLine();
           this->ui->text3->clear();
           this->ui->text3->insertPlainText(line);
           this->ui->text3->show();
           qDebug()<<line;
       }//读取低温数据并放在文本框内
       file1.close();

       QFile file2("C:/Users/33746/Desktop/high.txt");
       file2.open(QIODevice::ReadOnly | QIODevice::Text);//采取读模式实现只读取高温数据文档中的文本
       QTextStream in1(&file2);
       QString line1;
       while(!in1.atEnd())
       {
           line1=in1.readLine();
           this->ui->text4->clear();
           this->ui->text4->insertPlainText(line1);
           this->ui->text4->show();
           qDebug()<<line1;
       }//读取高温数据并放在文本框内
       file2.close();

    });//连接信号和槽，点击搜索后将最低温与最高温在界面进行显示

    connect(this->ui->pushButton_3,&QPushButton::clicked,this,[=](){
        QMessageBox info;
        info.information(this,"提示框","数据更新中");

        QFile file2("C:/Users/33746/Desktop/low.txt");
        file2.open(QIODevice::ReadOnly | QIODevice::Text);//采取读模式实现只读取低温数据文档中的文本
        QTextStream in(&file2);
        QString line;
        while(!in.atEnd())
        {
            line=in.readLine();
            this->ui->text3->clear();
            this->ui->text3->insertPlainText(line);
            this->ui->text3->show();
            qDebug()<<line;
        }//读取低温数据并放在文本框内
        file2.close();

        QFile file3("C:/Users/33746/Desktop/high.txt");
        file3.open(QIODevice::ReadOnly | QIODevice::Text);//采取读模式实现只读取高温数据文档中的文本
        QTextStream in1(&file3);
        QString line1;
        while(!in1.atEnd())
        {
            line1=in1.readLine();
            this->ui->text4->clear();
            this->ui->text4->insertPlainText(line1);
            this->ui->text4->show();
            qDebug()<<line1;
        }//读取高温数据并放在文本框内
        file3.close();

        QFile file("C:/Users/33746/Desktop/low.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        char key=' ';
        QTextStream out(&file);
        out<<key;
        file.close();

        QFile file1("C:/Users/33746/Desktop/high.txt");
        file1.open(QIODevice::WriteOnly | QIODevice::Text);
        char key1=' ';
        QTextStream out1(&file1);
        out1<<key1;
        file1.close();

    });//将所有数据清空后Python端接受到消息就开始处理新的数据

    SerialPortInit();
}

void MainWindow::SerialPortInit()
{

    ui->comboBox_2->addItem("9600");//设置波特率
    ui->comboBox_4->addItem("0");//校验位
    ui->comboBox_5->addItem("1");//设置停止位
    ui->comboBox_5->addItem("2");

    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->hide();

    ui->comboBox_2->setCurrentIndex(0);
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
         QSerialPort serial;
         serial.setPort(info);
         if(serial.open(QIODevice::ReadWrite))
         {
             ui->comboBox->addItem(serial.portName());
             serial.close();
         }
    }//检测串口

    serial=new QSerialPort;//新建串口对象
    serial->setPortName(ui->comboBox->currentText());//设置串口名称
    serial->open(QIODevice::ReadWrite);//打开串口

    serial->setBaudRate(QSerialPort::Baud4800);//设置波特率

    serial->setParity(QSerialPort::NoParity);
//    switch (ui->comboBox_4->currentIndex())//设置校验位
//     {
//          case 0:
//              serial->setParity(QSerialPort::NoParity);
//              break;
//          default:
//              break;
//     }

    serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
//     switch (ui->comboBox_5->currentIndex())//设置停止位
//     {
//          case 1:
//              serial->setStopBits(QSerialPort::OneStop);//停止位设置为1
//              break;
//          case 2:
//              serial->setStopBits(QSerialPort::TwoStop);//停止位设置为2
//              break;
//          default:
//              break;
//     }

     serial->setFlowControl(QSerialPort::NoFlowControl);//设置为默认控制不允许更改参数
                ui->comboBox->setEnabled(false);
                ui->comboBox_2->setEnabled(false);
                ui->comboBox_3->setEnabled(false);
                ui->comboBox_4->setEnabled(false);
                ui->comboBox_5->setEnabled(false);

                connect(ui->pushButton,&QPushButton::clicked,this,[=](){
                    serial->write(ui->text3->toPlainText().toLatin1());//将低温文本框中内容通过串口发送到单片机
                    serial->write("L");//尾部追加L字符意为该字符串信息为低温字符串
                    qDebug()<<ui->text3->toPlainText();

//                    QFile file("C:/Users/33746/Desktop/low.txt");
//                    file.open(QIODevice::WriteOnly | QIODevice::Text);
//                    char key=' ';
//                    QTextStream out(&file);
//                    out<<key;
//                    file.close();//发送完成后

                    QByteArray buf; //二进制
                    buf=serial->readAll();
                    if(!buf.isEmpty())
                    {
                        QString str=buf;
                        if(str.endsWith("END"))
                        {
                            qDebug()<<("I get");
                        }
                    }//接收下位机反馈信息
                    buf.clear();

                });

                connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
                    serial->write(ui->text4->toPlainText().toLatin1());//将高温文本框中内容通过串口发送到单片机
                    serial->write("H");//尾部追加H字符意为该字符串信息为高温字符串
                    qDebug()<<ui->text4->toPlainText();

//                    QFile file("C:/Users/33746/Desktop/high.txt");
//                    file.open(QIODevice::WriteOnly | QIODevice::Text);
//                    char key=' ';
//                    QTextStream out(&file);
//                    out<<key;
//                    file.close();

                    QByteArray buf; //二进制
                    buf=serial->readAll();
                    if(!buf.isEmpty())
                    {
                        QString str=buf;
                        if(str.endsWith("END"))
                        {
                            qDebug()<<("I get");
                        }
                    }//接收下位机反馈信息
                    buf.clear();

                });

}

MainWindow::~MainWindow()
{
    delete ui;
}
