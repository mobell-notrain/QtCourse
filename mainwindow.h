#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStack>
#include <QPushButton>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString calculation(bool *ok);

private slots:
    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();
    void on_btnPeriod_clicked();
    void on_btnDel_clicked();
    void on_btnClear_clicked();
    void on_btnEqual_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;

    QString operand;            // 当前正在输入的数字字符串
    QStack<QString> operands;   // 操作数栈
    QStack<QString> opcodes;    // 操作符栈

    QMap<int, QPushButton *> btnNums;   // 键盘按键 -> 按键控件的映射
};

#endif // MAINWINDOW_H
