#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent, QPlainTextEdit *textEdit) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_btFindNext_clicked()
{
    // TODO：查找逻辑在第 10 步补全
}

void SearchDialog::on_btCancel_clicked()
{
    accept();
}
