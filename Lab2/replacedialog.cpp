#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent,QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btFindNext_clicked()
{
    // TODO：查找逻辑在第 11 步补全
}

void ReplaceDialog::on_btCancel_clicked()
{
    accept();
}

void ReplaceDialog::on_btReplace_clicked()
{
    // TODO：单次替换在第 11 步实现
}

void ReplaceDialog::on_btAllReplace_clicked()
{
    // TODO：全部替换在第 11 步实现
}
