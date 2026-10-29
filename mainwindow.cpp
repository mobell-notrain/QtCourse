#include "mainwindow.h"
#include "ui_mainwindow.h"

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
