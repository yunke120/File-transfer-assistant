#include "tcpsever.h"
#include "ui_tcpsever.h"

TcpSever::TcpSever(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpSever)
{
    ui->setupUi(this);

    sever = new QTcpServer;
    socket = new QTcpSocket;

    connect(sever, &QTcpServer::newConnection, this, [=](){
        socket = sever->nextPendingConnection();
        QString ip = socket->peerAddress().toString();
        qint16 port = socket->peerPort();

        ui->textEdit->append(QString("[%1:%2]: connect successfully.").arg(ip).arg(port));
        ui->textEdit->append(QString("recvive data: %1").arg(QString(socket->readAll())));
    });
}

TcpSever::~TcpSever()
{
    delete ui;
}


void TcpSever::on_listen_clicked()
{
    QString ip = ui->IP->text();
    qint16 port = ui->Port->text().toInt();
    if(ip.isEmpty()) {
        sever->listen(QHostAddress::Any, port);
    }
    else {
        sever->listen(QHostAddress(ip), port);
    }
}
