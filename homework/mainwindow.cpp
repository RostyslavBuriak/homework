#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 4444);
    socket->waitForConnected();
    if(socket->state() == QAbstractSocket::ConnectedState)
       socket->write("e b.sh\0",7);
    socket->waitForReadyRead();
    char buff[1024]{};
    ui->label->setText(buff);
}


