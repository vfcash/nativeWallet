/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *newkey;
    QLineEdit *explore_address;
    QLineEdit *loginpriv;
    QFrame *line_2;
    QLabel *label_11;
    QDoubleSpinBox *amount;
    QLineEdit *topub;
    QLabel *label_10;
    QPushButton *send_trans;
    QLabel *label_12;
    QPushButton *login;
    QFrame *line_4;
    QLabel *label_17;
    QLabel *balance;
    QFrame *line_5;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_19;
    QLabel *label_20;
    QPushButton *view;
    QTextEdit *explore_result;
    QPushButton *privsend;
    QFrame *line_3;
    QFrame *line_8;
    QLabel *label_13;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(592, 666);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/favicon"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setDocumentMode(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        newkey = new QPushButton(centralwidget);
        newkey->setObjectName(QString::fromUtf8("newkey"));
        newkey->setGeometry(QRect(10, 10, 51, 31));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        newkey->setFont(font);
        explore_address = new QLineEdit(centralwidget);
        explore_address->setObjectName(QString::fromUtf8("explore_address"));
        explore_address->setGeometry(QRect(10, 210, 461, 31));
        loginpriv = new QLineEdit(centralwidget);
        loginpriv->setObjectName(QString::fromUtf8("loginpriv"));
        loginpriv->setGeometry(QRect(70, 10, 441, 31));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(10, 50, 571, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(460, 80, 101, 17));
        amount = new QDoubleSpinBox(centralwidget);
        amount->setObjectName(QString::fromUtf8("amount"));
        amount->setGeometry(QRect(460, 100, 121, 31));
        amount->setDecimals(3);
        amount->setMinimum(0.001000000000000);
        amount->setMaximum(4294967.294999999925494);
        amount->setSingleStep(0.001000000000000);
        topub = new QLineEdit(centralwidget);
        topub->setObjectName(QString::fromUtf8("topub"));
        topub->setGeometry(QRect(10, 140, 461, 31));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 120, 221, 20));
        send_trans = new QPushButton(centralwidget);
        send_trans->setObjectName(QString::fromUtf8("send_trans"));
        send_trans->setGeometry(QRect(470, 140, 51, 31));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        send_trans->setFont(font1);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(320, 100, 131, 20));
        label_12->setFont(font1);
        login = new QPushButton(centralwidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(520, 10, 61, 31));
        login->setFont(font);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(10, 100, 291, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_17 = new QLabel(centralwidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(30, 70, 131, 20));
        label_17->setFont(font1);
        balance = new QLabel(centralwidget);
        balance->setObjectName(QString::fromUtf8("balance"));
        balance->setGeometry(QRect(170, 70, 411, 20));
        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(10, 610, 571, 16));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 630, 111, 20));
        label_14->setTextFormat(Qt::RichText);
        label_14->setOpenExternalLinks(true);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(290, 630, 121, 20));
        label_15->setTextFormat(Qt::RichText);
        label_15->setOpenExternalLinks(true);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(160, 630, 121, 20));
        label_16->setTextFormat(Qt::RichText);
        label_16->setOpenExternalLinks(true);
        label_19 = new QLabel(centralwidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(420, 630, 71, 20));
        label_19->setTextFormat(Qt::RichText);
        label_19->setOpenExternalLinks(true);
        label_20 = new QLabel(centralwidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(500, 630, 61, 20));
        label_20->setTextFormat(Qt::RichText);
        label_20->setOpenExternalLinks(true);
        view = new QPushButton(centralwidget);
        view->setObjectName(QString::fromUtf8("view"));
        view->setGeometry(QRect(470, 210, 111, 31));
        view->setFont(font);
        explore_result = new QTextEdit(centralwidget);
        explore_result->setObjectName(QString::fromUtf8("explore_result"));
        explore_result->setGeometry(QRect(10, 240, 571, 361));
        explore_result->setReadOnly(true);
        privsend = new QPushButton(centralwidget);
        privsend->setObjectName(QString::fromUtf8("privsend"));
        privsend->setGeometry(QRect(530, 140, 51, 31));
        privsend->setFont(font1);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(10, 180, 41, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(centralwidget);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setGeometry(QRect(220, 180, 361, 16));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(60, 180, 251, 20));
        label_13->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "VF Cash Wallet / Qt", nullptr));
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        newkey->setText(QApplication::translate("MainWindow", "Nu", nullptr));
        explore_address->setText(QString());
        loginpriv->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "Amount:", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "To Address:", nullptr));
        send_trans->setText(QApplication::translate("MainWindow", "Send", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Send Transaction", nullptr));
        login->setText(QApplication::translate("MainWindow", "Login", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "Account Balance:", nullptr));
        balance->setText(QApplication::translate("MainWindow", "0 VFC", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "<a href=\"https://vfcash.uk/\">VF Cash Home</a>", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "<a href=\"https://x.vite.net/trade?symbol=VFC-000_BTC-000&category=BTC\">VGATE Exchange</a>", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "<a href=\"https://bihodl.com/#/exchange/vfc_usdt\">Bihodl Exchange</a>", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "<a href=\"https://t.me/vfcash\">Telegram</a>", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "<a href=\"https://discord.gg/VFa4A5v\">Discord</a>", nullptr));
        view->setText(QApplication::translate("MainWindow", "Load", nullptr));
        privsend->setText(QApplication::translate("MainWindow", "Priv", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Transaction Explorer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
