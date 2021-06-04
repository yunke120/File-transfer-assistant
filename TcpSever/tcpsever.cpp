#include "tcpsever.h"
#include "ui_tcpsever.h"

TcpSever::TcpSever(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpSever)
{
    ui->setupUi(this);

    sever = new QTcpServer;
    socket = new QTcpSocket;

    QString localHostName = QHostInfo::localHostName(); /* to get the host name of your computer. */

    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            ui->comboBox->addItem(address.toString()); /* to get all IPV4 addresses */
    }





    connect(sever, &QTcpServer::newConnection, this, [=](){
        socket = sever->nextPendingConnection();
        QString ip = socket->peerAddress().toString();
        quint16 port = socket->peerPort();

        ui->textEdit->append(QString("[%1:%2]: connect successfully.").arg(ip).arg(port));

        connect(socket, &QTcpSocket::readyRead, this, [=]() {
            ui->textEdit->append(QString("receive data: %1").arg(QString(socket->readAll())));
        });


    });
}

TcpSever::~TcpSever()
{
    delete ui;
}


void TcpSever::on_listen_clicked()
{
    QString ip = ui->comboBox->currentText();
    quint16 port = ui->Port->text().toUShort();
    if(ip.isEmpty()) {
        sever->listen(QHostAddress::Any, port);
    }
    else {
        if(sever->listen(QHostAddress(ip), port)) {
            ui->textEdit->append("listen successfully.");
        }else {
            ui->textEdit->append("failed listen");
        }

    }
}

void TcpSever::on_reserve_clicked()
{

}















