#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->ipAddress->setText("192.168.1.2");
    ui->ipAddress->setText("127.0.0.1");
    ui->Port->setText("55555");

    tcpClient = new QTcpSocket(this);
    tcpClient->abort();
    connect(ui->Ok,&QAbstractButton::clicked,this,
            &MainWindow::Set_IP_Port);
    connect(ui->pushButton,&QAbstractButton::clicked,this,
            &MainWindow::Send_button);
    connect(ui->Ok,&QAbstractButton::clicked,this,
            &MainWindow::Get_Data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Send_button()
{
    tcpClient->write(ui->lineEdit->text().toUtf8());
    ui->lineEdit->clear();
}

void MainWindow::Get_Data()
{
    connect(tcpClient,&QTcpSocket::readyRead,
            [=](){
        QByteArray temp = tcpClient->readAll();
        ui->textBrowser->append(temp);
        temp.clear();
    });
}

void MainWindow::Set_IP_Port()
{
    QString ip_temp = ui->ipAddress->text();

    ui->textBrowser->append(ip_temp);
    unsigned short port = ui->Port->text().toUShort();
    tcpClient->connectToHost(ip_temp,port,QTcpSocket::ReadWrite);

    ui->textBrowser->append(QString::number(port));
    tcpClient->write("PC_CLIENT");
}

void MainWindow::on_cclean_clicked()
{
    ui->textBrowser->clear();
}
