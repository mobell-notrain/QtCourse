#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 数字按键统一连接到同一个槽，通过 sender() 区分具体是哪个按钮
    connect(ui->btnNum0, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum1, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum2, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum3, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum4, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum5, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum6, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum7, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum8, &QPushButton::clicked, this, &MainWindow::btnNumClicked);
    connect(ui->btnNum9, &QPushButton::clicked, this, &MainWindow::btnNumClicked);

    // 二元运算符
    connect(ui->btnPlus, &QPushButton::clicked, this, &MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnMinus, &QPushButton::clicked, this, &MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnDivide, &QPushButton::clicked, this, &MainWindow::btnBinaryOperatorClicked);

    // 一元运算符
    connect(ui->btnPercentage, &QPushButton::clicked, this, &MainWindow::btnUnaryOperatorClicked);
    connect(ui->btn1x, &QPushButton::clicked, this, &MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnSqure, &QPushButton::clicked, this, &MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnRoot, &QPushButton::clicked, this, &MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnPlusMinus, &QPushButton::clicked, this, &MainWindow::btnUnaryOperatorClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    // 初始状态屏幕上是 "0"，此时按下的数字直接覆盖
    if (operand == "0") {
        operand = btn->text();
    } else {
        operand += btn->text();   // 否则追加到已有数字后面
    }

    ui->display->setText(operand);
}

void MainWindow::on_btnPeriod_clicked()
{
    // 一个操作数里只允许出现一个小数点
    if (operand.contains("."))
        return;

    // 还没输入数字（或刚出错）时按下小数点，自动补前导 0
    if (operand.isEmpty() || operand == "Error") {
        operand = "0.";
    } else {
        operand += ".";
    }

    ui->display->setText(operand);
}

void MainWindow::on_btnDel_clicked()
{
    if (operand.isEmpty()) return;

    operand.chop(1);              // 删掉最后一个字符
    if (operand.isEmpty()) {
        operand = "0";            // 删光了就回到初始状态
    }

    ui->display->setText(operand);
}

void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText("0");
}

void MainWindow::btnBinaryOperatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    // 先把当前输入的数字压栈，再清空 operand，准备接收下一个操作数
    if (!operand.isEmpty()) {
        operands.push(operand);
        operand.clear();
    }

    opcodes.push(btn->text());

    // 栈里已经有两个操作数时立刻计算，结果继续留在栈顶参与后续运算
    if (operands.size() >= 2) {
        bool ok = false;
        QString res = calculation(&ok);
        if (ok) {
            ui->display->setText(res);
        } else {
            ui->display->setText("Error");
            operand = "Error";
        }
    }
}

void MainWindow::btnUnaryOperatorClicked()
{
    // operand 为空时（刚算完或刚按过运算符），以屏幕上显示的数字为操作对象
    QString current = (operand.isEmpty() || operand == "Error")
                          ? ui->display->text() : operand;
    if (current.isEmpty() || current == "Error")
        return;

    double result = current.toDouble();
    QString op = qobject_cast<QPushButton *>(sender())->text();

    if (op == "%") {
        result /= 100.0;
    } else if (op == "1/x") {
        if (result == 0) {             // 0 不能做除数
            ui->display->setText("Error");
            operand = "Error";
            return;
        }
        result = 1.0 / result;
    } else if (op == "x^2") {
        result *= result;
    } else if (op == "√x") {
        if (result < 0) {              // 负数不能开平方
            ui->display->setText("Error");
            operand = "Error";
            return;
        }
        result = qSqrt(result);
    } else if (op == "±") {
        result = -result;
    }

    ui->display->setText(QString::number(result, 'g', 10));
    operand.clear();   // 结果已经上屏，下次按数字重新开始输入
}

void MainWindow::on_btnEqual_clicked()
{
    // 把最后输入的数字也压入栈
    if (!operand.isEmpty()) {
        operands.push(operand);
        operand.clear();
    }

    bool ok = false;
    QString res = calculation(&ok);
    if (ok) {
        ui->display->setText(res);
    } else {
        ui->display->setText("Error");
        operand = "Error";
    }
}

QString MainWindow::calculation(bool *ok)
{
    if (operands.size() < 2 || opcodes.isEmpty()) {
        if (ok) *ok = false;
        return "0";
    }

    // 栈是后进先出，先弹出的才是右操作数
    double operand2 = operands.top().toDouble();
    operands.pop();
    double operand1 = operands.top().toDouble();
    operands.pop();

    QString op = opcodes.top();
    opcodes.pop();

    double result = 0;
    if (op == "+") {
        result = operand1 + operand2;
    } else if (op == "-") {
        result = operand1 - operand2;
    } else if (op == "*" || op == "×") {
        result = operand1 * operand2;
    } else if (op == "/" || op == "÷") {
        result = operand1 / operand2;
    }

    if (ok) *ok = true;
    return QString::number(result, 'g', 10);
}
