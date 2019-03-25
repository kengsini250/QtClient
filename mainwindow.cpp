#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setAttribute(Qt::WA_InputMethodEnabled,true);

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
    QString data = ui->lineEdit->text();
    tcpClient->write(data.toUtf8());
    ui->lineEdit->clear();
}

void MainWindow::Get_Data()
{
    connect(tcpClient,&QTcpSocket::readyRead,
            [=](){
        QByteArray temp = tcpClient->readAll();
        ui->textBrowser->append(tcpClient->peerAddress().toString());
        ui->textBrowser->append(QString::number(tcpClient->peerPort()));
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
}

void MainWindow::on_cclean_clicked()
{
    ui->textBrowser->clear();
}
