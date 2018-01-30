#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <qpushbutton.h>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUntitled = true;
    curFile = "未命名.txt";
    setWindowTitle(curFile);

    findDlg = new QDialog(this);
    findDlg->setWindowTitle("查找");
    findLineEdit = new QLineEdit(findDlg);
    QPushButton* btn = new QPushButton("查找下一个", findDlg);
    QVBoxLayout* layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn, SIGNAL(clicked()), this, SLOT(showFindText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile() {
    if (mayBeSaved()) {
        isUntitled = true;
        curFile = "未命名.txt";
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::mayBeSaved() {
    if (ui->textEdit->document()->isModified()) {
        QMessageBox box;
        box.setWindowTitle("警告");
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + " 尚未保存， 是否保存？");
        QPushButton* yesBtn = box.addButton("是（&Y)", QMessageBox::YesRole);
        box.addButton("否(&N)", QMessageBox::NoRole);
        QPushButton *cancelBtn= box.addButton("取消", QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn) {
            return save();
        }
        else if (box.clickedButton() == cancelBtn) {
            return false;
        }
    }

    return true;
}

bool MainWindow::save() {
    if (isUntitled) {
        return saveAs();
    }
    else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "另存为", curFile);
    if (fileName.isEmpty()) {
        return false;
    }

    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "多文档编辑器", tr("无法写入文件 %1: \n %2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    isUntitled = false;

    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);

    return true;
}

bool MainWindow::loadFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "多文档编辑器", tr("无法读取文件 %1 \n %2.").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);

    return true;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (mayBeSaved()) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::on_action_N_triggered()
{
    newFile();
}

void MainWindow::on_action_S_triggered()
{
    save();
}

void MainWindow::on_action_A_triggered()
{
    saveAs();
}

void MainWindow::on_action_O_triggered()
{
    if (mayBeSaved()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_action_C_triggered()
{
    if (mayBeSaved()) {
        ui->textEdit->clear();
        ui->textEdit->setVisible(false);
    }
}

void MainWindow::on_action_X_triggered()
{
    on_action_C_triggered();
    qApp->quit();
}

void MainWindow::on_action_Z_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_X_2_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_C_2_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_V_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if (!ui->textEdit->find(str, QTextDocument::FindBackward)) {
        QMessageBox::warning(this, "查找", tr("找不到%1").arg(str));
    }
}

void MainWindow::on_action_F_triggered()
{
    findDlg->show();
}
