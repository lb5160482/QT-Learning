#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>

class QLineEdit;
class QDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newFile();
    bool mayBeSaved();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString& fileName);

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_action_N_triggered();

    void on_action_S_triggered();

    void on_action_A_triggered();

    void on_action_O_triggered();

    void on_action_C_triggered();

    void on_action_X_triggered();

    void on_action_Z_triggered();

    void on_action_X_2_triggered();

    void on_action_C_2_triggered();

    void on_action_V_triggered();

    void showFindText();

    void on_action_F_triggered();

private:
    Ui::MainWindow *ui;
    bool isUntitled;
    QString curFile;
    QLineEdit* findLineEdit;
    QDialog* findDlg;
};

#endif // MAINWINDOW_H
