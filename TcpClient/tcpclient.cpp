#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);

    socket = new QTcpSocket;

    connect(socket, &QTcpSocket::connected, this, [=](){
        ui->textEdit->append("connect successfully.");
    });


    connect(socket, &QTcpSocket::readyRead, this, [=](){
        ui->textEdit->append(socket->readAll());
    });
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::on_connect_clicked()
{
    QString ip = ui->IP->text();
    qint16 port = ui->port->text().toInt();

    socket->connectToHost(QHostAddress(ip), port);
}


void TcpClient::on_send_clicked()
{
    QString text = ui->textEdit->toPlainText();
    socket->write(text.toUtf8().data());
}



void TcpClient::on_disconnect_clicked()
{
    socket->disconnectFromHost();
}
