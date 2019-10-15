//    //Sign the block
//    QByteArray tba = QByteArray::fromRawData((const char*)&t, sizeof(struct trans));
//    QByteArray tohash = QCryptographicHash::hash(tba, QCryptographicHash::Sha3_256);
//    char bohash[256];
//    memset(bohash, 0, sizeof(bohash));
//    len = 256;
//    b58enc(bohash, &len, (const void*)tohash.data(), ECC_CURVE);

//    msgBox.setText(rthash);
//    msgBox.exec();

//    msgBox.setText(bohash);
//    msgBox.exec();

//    thash.truncate(ECC_CURVE);
//    if(ecdsa_sign(priv, (const uint8_t*)thash.data(), t.owner.key) == 0)

#include <QProcess>
#include <QLocale>
#include <QDir>
#include <QUrl>
#include <QThread>
#include <QTextStream>
#include <QMessageBox>
#include <QClipboard>
#include <QScrollBar>
#include <QCryptographicHash>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDesktopServices>

#include "base58.h"
#include "crc64.h"
#include "ecc.h"

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

    ui->amount->setEnabled(false);
    ui->topub->setEnabled(false);
    ui->send_trans->setEnabled(false);
    ui->privsend->setEnabled(false);

    timerId = startTimer(9000);

    api_url = "http://vfcash.co.uk";

    //Build the window
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::resync()
{
    if(QString(bpub) != "")
    {
        QString bal = getWeb(api_url + "/rest.php?balance=" + QString(bpub));
        bbal = bal.toDouble();
        if(bal != "" && bal[0] != 'p')
            ui->balance->setText(double_format(bal.toDouble()) + " VFC");
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId)
        resync();
}

void MainWindow::on_privsend_clicked()
{
    //Check input is good
    if(ui->topub->text() == "")
    {
        QMessageBox msgBox;
        msgBox.setText("Please insert a receiver / send to address.");
        msgBox.exec();
        return;
    }

    if(bbal <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("You do not have the balance to make this transaction of " + QString::number(ui->amount->value()) + " VFC.");
        msgBox.exec();
        return;
    }

    const time_t st = time(nullptr);
    ui->privsend->setEnabled(false);


    //base58 to bytes
    uint8_t mpub[ECC_CURVE+1];
    size_t len = ECC_CURVE+1;
    memset(mpub, 0, sizeof(priv));
    b58tobin(mpub, &len, ui->topub->text().toUtf8(), (size_t)ui->topub->text().length());

    //Construct Transaction
    struct trans t;
    memset(&t, 0, sizeof(struct trans));
    memcpy(t.from.key, pub, ECC_CURVE+1);
    memcpy(t.to.key, mpub, ECC_CURVE+1);
    t.amount = (uint32_t)(ui->amount->value() * 1000);

    //Creating a Transaction UID
    time_t ltime = time(nullptr);
    char suid[256];
    snprintf(suid, sizeof(suid), "%s/%s", asctime(localtime(&ltime)), bpub); //timestamp + base58 from public key
    t.uid = crc64(0, (unsigned char*)suid, strlen(suid));

    //Get the signing hash
    QString rthash = getWeb(api_url + "/rest.php?uid=" + QString::number(t.uid) + "&frompub=" + bpub + "&topub=" + ui->topub->text() + "&amount=" + QString::number(ui->amount->value()));
    uint8_t thash[ECC_CURVE];
    len = ECC_CURVE;
    memset(thash, 0, sizeof(thash));
    b58tobin(thash, &len, rthash.toUtf8(), (size_t)rthash.toUtf8().length());

    //Sign transaction with hash
    if(ecdsa_sign(priv, thash, t.owner.key) == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Failed to sign the transaction.");
        msgBox.exec();
        return;
    }

    //Construct packet
    const uint32_t origin = 0;
    char p[147];
    p[0] = 't';
    char* ofs = p + 1;
    memcpy(ofs, &origin, sizeof(uint32_t));
    ofs += sizeof(uint32_t);
    memcpy(ofs, &t.uid, sizeof(uint64_t));
    ofs += sizeof(uint64_t);
    memcpy(ofs, t.from.key, ECC_CURVE+1);
    ofs += ECC_CURVE+1;
    memcpy(ofs, t.to.key, ECC_CURVE+1);
    ofs += ECC_CURVE+1;
    memcpy(ofs, &t.amount, sizeof(uint32_t));
    ofs += sizeof(uint32_t);
    memcpy(ofs, t.owner.key, ECC_CURVE*2);

    //Base58 encode
    char b58p[384];
    len = 384;
    memset(b58p, 0, len);
    b58enc(b58p, &len, p, 147);

    //Send using the REST API packet sender
    getWeb(api_url + "/rest.php?stp=" + QString(b58p));

    //Ensure full 3 sec wait between transactions
    time_t delta = abs(time(nullptr) - st);
    while(delta < 6)
    {
        QThread::sleep(1);
        delta = time(nullptr) - st;
    }

    QMessageBox msgBox;
    msgBox.setText("Transaction sent.\nTXID: " + QString::number(t.uid));
    msgBox.exec();

    //Prep ui
    ui->explore_address->setText(ui->topub->text());
    on_view_clicked();

    //Done
    ui->privsend->setEnabled(true);
}

void MainWindow::on_send_trans_clicked()
{
    if(ui->topub->text() == "")
    {
        QMessageBox msgBox;
        msgBox.setText("Please insert a receiver / send to address.");
        msgBox.exec();
        return;
    }

    if(bbal <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("You do not have the balance to make this transaction of " + QString::number(ui->amount->value()) + " VFC.");
        msgBox.exec();
        return;
    }

    const time_t st = time(nullptr);
    ui->send_trans->setEnabled(false);

    //Send over the SSL restful api
    QString rd = getWeb(api_url + "/rest.php?frompriv=" + bpriv + "&topub=" + ui->topub->text() + "&amount=" + QString::number(ui->amount->value()));

    //Ensure full 3 sec wait between transactions
    time_t delta = abs(time(nullptr) - st);
    while(delta < 3)
    {
        QThread::sleep(1);
        delta = time(nullptr) - st;
    }

    QMessageBox msgBox;
    msgBox.setText(rd.replace(" > ", " > \n").replace("[H[J", "").replace("Transaction Sent, but unable to verify it's success. Refer to sent transactions for confirmation. Trying again..\n\n", ""));
    msgBox.exec();

    ui->explore_address->setText(ui->topub->text());
    on_view_clicked();

    //Done
    ui->send_trans->setEnabled(true);
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
            if(QString(bpub) == "236h7pukvqi6u8ADu53erbWyLYXNyNEuB9BRNMXtVKUfZ")
            {
                memset(priv, 0, sizeof(priv));
                memset(bpriv, 0, sizeof(bpriv));
                memset(pub, 0, sizeof(pub));
                memset(bpub, 0, sizeof(bpub));
                QMessageBox msgBox;
                msgBox.setText("This is not a valid private key.");
                msgBox.exec();
                return;
            }
        }

        ui->login->setText("Logout");
        ui->loginpriv->setText(bpub);
        ui->loginpriv->setReadOnly(true);
        ui->newkey->setText("copy");
        ui->explore_address->setText(bpub);

        ui->amount->setEnabled(true);
        ui->topub->setEnabled(true);
        ui->send_trans->setEnabled(true);
        ui->privsend->setEnabled(true);

        on_view_clicked();
    }
    else
    {
        ui->login->setText("Login");
        ui->loginpriv->setText("");
        ui->loginpriv->setReadOnly(false);
        ui->newkey->setText("Nu");
        ui->balance->setText("0 VFC");
        ui->amount->setValue(0.001);
        ui->topub->setText("");
        bpub[0] = 0x00;
        bpriv[0] = 0x00;

        ui->amount->setEnabled(false);
        ui->topub->setEnabled(false);
        ui->send_trans->setEnabled(false);
        ui->privsend->setEnabled(false);
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
    QScrollBar *scrollbar = ui->explore_result->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
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

        //Append created private key to file as backup
        QFile file(QDir::homePath() + "/.vfc-keys.priv");
        if (file.open(QIODevice::Append))
        {
            QTextStream stream(&file);
            stream << bpriv << endl;
        }

        //Set private key in dialog
        ui->loginpriv->setText(bpriv);
    }
    else
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ui->loginpriv->text());
    }
}





