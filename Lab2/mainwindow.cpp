#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AboutDialog.h"
#include "SearchDialog.h"
#include "ReplaceDialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionStatusBar, &QAction::toggled, ui->statusbar, &QStatusBar::setVisible);
    connect(ui->actionToolBar, &QAction::toggled, ui->toolBar, &QToolBar::setVisible);

    textChanged = false;
    on_actionNew_triggered();

    statusLabel.setMaximumWidth(150);
    statusLabel.setText("lenth:"+QString::number(0)+"   lines:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    lengthLabel = new QLabel(this);
    lengthLabel->setMaximumWidth(150);
    lengthLabel->setText("Ln:"+QString::number(0)+"  Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(lengthLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText("liyuanhao");
    ui->statusbar->addPermanentWidget(author);

    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if ( mode == QPlainTextEdit::NoWrap ) {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionWrap->setChecked(false);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionWrap->setChecked(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}

void MainWindow::on_actionFind_triggered()
{
    SearchDialog dlg(this,ui->textEdit);
    dlg.exec();
}

void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog dlg(this,ui->textEdit);
    dlg.exec();
}

void MainWindow::on_actionNew_triggered()
{
    if(!userEditConfirmed()){
        return;
    }
    filePath = "";
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));

    textChanged = false;
}

void MainWindow::on_actionOpen_triggered()
{
    if(!userEditConfirmed()){
        return;
    }
    QString filename=
        QFileDialog::getOpenFileName(this,"打开文件",".",tr("Text file (*.txt);;All(*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"..","打开文件失败");
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

    textChanged = false;
}

void MainWindow::on_actionSave_triggered()
{
    if(filePath==""){
        QString filename=
            QFileDialog::getSaveFileName(this,"baocun 文件",".",tr("Text file (*.txt)"));

        QFile file(filename);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"..","打开保存文件失败");
            return;
        }

        filePath = filename;
    }
    QFile file(filePath);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","打开保存文件失败");
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    textChanged = false;
}

void MainWindow::on_actionA_triggered()
{
    QString filename=
        QFileDialog::getSaveFileName(this,"baocun 文件",".",tr("Text file (*.txt)"));

    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","打开保存文件失败");
        return;
    }

    filePath = filename;
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}

void MainWindow::on_textEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*"+this->windowTitle());
        textChanged= true;
    }

    statusLabel.setText("lenth:"+QString::number(ui->textEdit->toPlainText().length())+
                        "   lines:"+QString::number(ui->textEdit->document()->lineCount()));

}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){
        QString path = filePath != "" ? filePath : "无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否更改保存到\n") + "\"" + path+"\" ?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        int r = msg.exec();
        switch(r){
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }

    return true;
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCutting_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionBack_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionNext_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(color.name()));
    }
}

void MainWindow::on_actionBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(color.name()));
    }
}

void MainWindow::on_actionFontBackgroundColor_triggered()
{

}

void MainWindow::on_actionWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if ( mode == QPlainTextEdit::NoWrap ) {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionWrap->setChecked(true);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionWrap->setChecked(false);
    }
}

void MainWindow::on_actionSize_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
        ui->textEdit->setFont(font);
}

void MainWindow::on_actionStatusBar_triggered()
{

}

void MainWindow::on_actionToolBar_triggered()
{

}

void MainWindow::on_actionAll_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionExit_triggered()
{
    if(userEditConfirmed())
        exit(0);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = ui->textEdit->textCursor().position();
    QString text = ui->textEdit->toPlainText();

    for (int i = 0; i < pos; i++) {
        if ( text[i] == '\n' ) {
            ln ++;
            flg = i;
        }
    }

    flg ++;
    col = pos - flg;

    if (lengthLabel != nullptr) {
        lengthLabel->setText("Ln:" + QString::number(ln + 1) + "  Col:" + QString::number(col + 1));
    }
}
