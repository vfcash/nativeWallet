#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "base58.h"
#include "crc64.h"
#include "ecc.h"
#include "sha3.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void timerEvent(QTimerEvent *event);
    int timerId;

protected:
    Ui::MainWindow *ui;

    uint8_t pub[ECC_CURVE+1];
    uint8_t priv[ECC_CURVE];
    char bpub[256];
    char bpriv[256];

    QString getWeb(QString url);
    QString api_url;
    void resync();

private slots:
    void on_newkey_clicked();
    void on_send_trans_clicked();
    void on_login_clicked();
    void on_explore_address_returnPressed();
    void on_view_clicked();
};
#endif // MAINWINDOW_H
