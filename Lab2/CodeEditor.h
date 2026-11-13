#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    int lineNumberAreaWidth() const;
    void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void highlightCurrentLine();

public slots:
    void hideLineNumberArea(bool flag);

private:
    // 前向声明内部的行号栏类
    class LineNumberArea;

    QWidget *lineNumberArea;
};

// 行号栏的具体实现（嵌套类）
class CodeEditor::LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor) {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // CODEEDITOR_H