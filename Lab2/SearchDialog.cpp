#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>

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
    QString target = ui->searchText->text();

    if(target == "" || pTextEdit == nullptr){
        return;
    }

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();

    int index = -1;

    if(ui->rbDown->isChecked()){
        index = text.indexOf(target, c.position(),
                             ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        } else {
            QMessageBox::information(this, "提示", "未找到目标文本");
        }
    }
    else if(ui->rbUp){
        index = text.lastIndexOf(target, c.position() - text.length()-1,ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        if(index >= 0){
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        } else {
            QMessageBox::information(this, "提示", "未找到目标文本");
        }
    }




}

void SearchDialog::on_btCancel_clicked()
{
    accept();
}

