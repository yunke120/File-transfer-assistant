#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

private slots:

    void on_send_clicked();

    void on_connect_clicked();

    void on_disconnect_clicked();

private:
    Ui::TcpClient *ui;
    QTcpSocket *socket;
};
#endif // TCPCLIENT_H
