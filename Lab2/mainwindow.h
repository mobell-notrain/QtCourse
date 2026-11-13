#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_actionAbout_triggered();

    void on_actionFind_triggered();

    void on_actionReplace_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionA_triggered();

    void on_textEdit_textChanged();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCutting_triggered();

    void on_actionBack_triggered();

    void on_actionNext_triggered();

    void on_actionAll_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    QString filePath;
    bool textChanged;

    bool userEditConfirmed();
};
#endif // MAINWINDOW_H
