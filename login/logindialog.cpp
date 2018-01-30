#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
//    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->usrLineEdit->setPlaceholderText("请输入用户名");
    ui->pwdLineEdit->setPlaceholderText("请输入密码");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    if (ui->usrLineEdit->text().trimmed() == "lb5160482" &&
            ui->pwdLineEdit->text().trimmed() == "Lb5160482!") {
        accept();
    }
    else {
        QMessageBox::warning(this, "Warning", "User name or password not correct!", QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}
