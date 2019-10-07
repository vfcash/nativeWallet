#include <QProcess>
#include <QLocale>
#include <QDir>
#include <QUrl>
#include <QThread>
#include <QTextStream>
#include <QMessageBox>
#include <QClipboard>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDesktopServices>

#include "base58.h"
#include "crc64.h"
#include "ecc.h"
#include "sha3.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"


QString int_format(int i)
{
    return QLocale(QLocale::English).toString(i);
}

QString double_format(double d)
{
    return QLocale(QLocale::English).toString(d, 'f', 3);
}

QString MainWindow::getWeb(QString url)
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    return response->readAll();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    memset(bpub, 0, sizeof(bpub));
    memset(bpriv, 0, sizeof(bpriv));

    ui->setupUi(this);
    ui->statusbar->hide();

    timerId = startTimer(9000);

    api_url = "http://91.148.141.219";

    //Build the window
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::resync()
{
    on_view_clicked();

    if(QString(bpub) != "")
    {
        QString bal = getWeb(api_url + "/rest.php?balance=" + QString(bpub));
        if(bal != "" && bal[0] != 'p')
            ui->balance->setText(double_format(bal.toDouble()) + " VFC");
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId)
        resync();
}

void MainWindow::on_send_trans_clicked()
{
    //
}

void MainWindow::on_login_clicked()
{
    if(ui->loginpriv->text() == "")
        return;

    if(ui->login->text() == "Login")
    {
        size_t len = 32;
        memset(priv, 0, sizeof(priv));
        b58tobin(priv, &len, ui->loginpriv->text().toUtf8(), (size_t)ui->loginpriv->text().length());
        memcpy(bpriv, ui->loginpriv->text().toUtf8(), (size_t)ui->loginpriv->text().length());
        if(ecc_get_pubkey(pub, priv))
        {
            memset(bpub, 0, sizeof(bpub));
            len = 256;
            b58enc(bpub, &len, pub, ECC_CURVE+1);
        }

        ui->login->setText("Logout");
        ui->loginpriv->setText(bpub);
        ui->loginpriv->setReadOnly(true);
        ui->newkey->setText("copy");
        ui->explore_address->setText(bpub);

        resync();
    }
    else
    {
        ui->login->setText("Login");
        ui->loginpriv->setText("");
        ui->loginpriv->setReadOnly(false);
        ui->newkey->setText("Nu");
        ui->balance->setText("0 VFC");
        bpub[0] = 0x00;
        bpriv[0] = 0x00;
    }

}

void MainWindow::on_view_clicked()
{
    if(ui->explore_address->text() == "")
        return;

    QString fr = "";
    QString r = getWeb(api_url + "/rest.php?all=" + ui->explore_address->text());
    QStringList l = r.split("\n");
    foreach(QString v, l)
    {
        QStringList l2 = v.split(",");
        if(l2.length() > 3)
            fr += l2[0] + ", " + l2[3] + ", " + l2[1] + ", " + l2[2] + "\n";
    }
    ui->explore_result->setText(fr);
}

void MainWindow::on_explore_address_returnPressed()
{
    on_view_clicked();
}

void MainWindow::on_newkey_clicked()
{
    if(ui->login->text() == "Login")
    {
        //Make key pair
        ecc_make_key(pub, priv);

        //Dump Base58
        memset(bpub, 0, sizeof(bpub));
        memset(bpriv, 0, sizeof(bpriv));
        size_t len = 256;
        b58enc(bpub, &len, pub, ECC_CURVE+1);
        b58enc(bpriv, &len, priv, ECC_CURVE);

        //Set private key in dialog
        ui->loginpriv->setText(bpriv);
    }
    else
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ui->loginpriv->text());
    }
}



