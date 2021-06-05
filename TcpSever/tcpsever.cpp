#include "tcpsever.h"
#include "ui_tcpsever.h"

TcpSever::TcpSever(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpSever)
{
    ui->setupUi(this);

    sever = new QTcpServer;
    socket = new QTcpSocket;


    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
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
        uint16_t port = socket->peerPort();
        ui->textEdit->append(QString("[%1:%2]: connect successfully.").arg(ip).arg(port));
        ui->progressBar->setValue(0);
        file = new QFile;
        in = new QDataStream;
        static uint64_t total_size = 0;
        static uint64_t file_size = 0;
        connect(socket, &QTcpSocket::readyRead, this, [=]() {
            QByteArray array = socket->readAll();
            if(QString(array).left(5) == "begin") {
                ui->textEdit->append(QString(array));
                QStringList l = QString(array).split(" ");
                file_size = l.at(2).toUInt();

                QString file_name = "./" + QString(array).split(" ").at(1);
                ui->textEdit->append(QString("file will save at the path of [%1]").arg(file_name));

                ui->progressBar->setValue(0);
                file->setFileName(file_name);

                if(file->open(QIODevice::WriteOnly)) {
                    in->setVersion(QDataStream::Qt_4_9);
                    in->setDevice(file);
                    ui->textEdit->append("create file successfully");
                    QString str = "DATA";
                    socket->write(str.toLatin1().data(),str.length());
                }else {
                    ui->textEdit->append("failed to create file");
                }

            }
            else {
                total_size += array.size();
                int value = (double(total_size) / file_size) * 100;
                ui->progressBar->setValue(value);
                in->writeRawData(array.data(), array.size());
                if(value == 100) file->close();

            }


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















