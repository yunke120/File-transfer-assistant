﻿#ifndef TCPSEVER_H
#define TCPSEVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>


QT_BEGIN_NAMESPACE
namespace Ui { class TcpSever; }
QT_END_NAMESPACE

class TcpSever : public QWidget
{
    Q_OBJECT

public:
    TcpSever(QWidget *parent = nullptr);
    ~TcpSever();

private slots:
    void on_listen_clicked();

private:
    Ui::TcpSever *ui;

    QTcpServer *sever;
    QTcpSocket *socket;
};
#endif // TCPSEVER_H