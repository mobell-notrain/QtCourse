#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

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

void ReplaceDialog::on_btCancel_clicked()
{
    accept();
}


void ReplaceDialog::on_btReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();
    QString text = pTextEdit->toPlainText();

    QString selText = pTextEdit->textCursor().selectedText();

    if(selText == target)
        pTextEdit->insertPlainText(to);
}


void ReplaceDialog::on_btAllReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    QTextDocument::FindFlags flags;
    if (ui->cbCaseSensitive->isChecked()) {
        flags |= QTextDocument::FindCaseSensitively;
    }

    QTextCursor originalCursor = pTextEdit->textCursor();

    QTextCursor cursor = pTextEdit->textCursor();
    cursor.movePosition(QTextCursor::Start);
    pTextEdit->setTextCursor(cursor);

    cursor.beginEditBlock();

    int count = 0;
    while (pTextEdit->find(target, flags)) {
        QTextCursor currentCursor = pTextEdit->textCursor();
        currentCursor.insertText(to);
        count++;
    }

    cursor.endEditBlock();

    pTextEdit->setTextCursor(originalCursor);
}

