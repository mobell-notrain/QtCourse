# Lab2 实验日志：简单文本编辑器

- 课程：Qt 应用程序开发（2026 年秋季）
- 实验：实验二 简单文本编辑器（Lab2）
- 分支：`Lab2`
- 工程位置：`Lab2/`，工具栏图标：`RES/`

按实验报告“实验步骤及结果”列出的 12 个要点拆分：完成一个要点提交一次、记录一条日志，
提交顺序与要点顺序一致，每条日志对应本分支上的一次提交。

> 补录说明：实验过程中没有及时提交 Git 日志，本日志于 2026-11-13 依据最终工程与实验报告
> 按步骤拆分补录。每个提交只包含该步骤所需的代码，最后一步的代码与本地工程完全一致。

---

## 步骤 1 / 12：UI 界面布局与设计：菜单栏、工具栏、QPlainTextEdit 与 layoutMargins

- 目标：把实验报告的界面参考图落成可运行的窗口骨架：菜单栏、工具栏、编辑区三部分，并且用布局管理器而不是绝对坐标来摆放控件。
- 改动文件：
  - `README.md`
  - `.gitignore`
  - `Lab2/.gitignore`
  - `Lab2/Lab2.pro`
  - `Lab2/SearchDialog.cpp`
  - `Lab2/main.cpp`
  - `Lab2/mainwindow.cpp`
  - `Lab2/mainwindow.h`
  - `Lab2/mainwindow.ui`
  - `Lab2/replacedialog.cpp`
  - `Lab2/res.qrc`
  - `RES/add_active.png`
  - `RES/all.png`
  - `RES/back.png`
  - `RES/copy.png`
  - `RES/cutting.png`
  - `RES/fileconversion.png`
  - `RES/find.png`
  - `RES/new.png`
  - `RES/next.png`
  - `RES/openfile.png`
  - `RES/paste.png`
  - `RES/save.png`
  - `RES/tool.png`
  - `RES/wrap.png`
  - `RES/zhuangtai.png`
  - `RES/ziti.png`
- 关键实现：
  - 新建 Lab2 工程（Lab2.pro：QT += widgets、CONFIG += c++17），Qt Creator 生成的 .gitignore 一并纳入版本库
  - mainwindow.ui：QVBoxLayout（spacing = 0、left/top/right margin = 2）+ QPlainTextEdit（textEdit）
  - 22 个 Action：actionNew/Open/Save/A/Exit、actionBack/Next/Copy/Paste/Cutting、actionFind/Replace/Size/All/Wrap、actionFontColor/BackgroundColor/FontBackgroundColor、actionToolBar/StatusBar、actionAbout
  - 菜单栏 6 个菜单按功能分组，工具栏用 3 个分隔器切成 4 段
  - res.qrc 引入 RES/ 下 16 个 png 图标（新建、打开、保存、撤销、恢复、复制、剪切、粘贴、查找、替换、字体、换行、状态栏、工具栏、另存为、全选）
- 验证：
  - qmake + mingw32-make Debug 构建通过，无编译告警以外的错误
  - 运行后显示空编辑器窗口，6 个菜单、工具栏 4 组按钮、状态栏齐全
  - 拖动窗口大小时编辑区跟随缩放（布局生效，非固定坐标）
- 备注：此时 22 个 Action 只有界面没有槽函数，点下去不会有反应，属于本步的预期状态。

## 步骤 2 / 12：设计关于对话框

- 目标：多窗口程序的第一个独立窗口：用 Designer 新建 Dialog 表单，并在主窗口里以模态方式打开。
- 改动文件：
  - `Lab2/AboutDialog.cpp`
  - `Lab2/AboutDialog.h`
  - `Lab2/AboutDialog.ui`
  - `Lab2/Lab2.pro`
  - `Lab2/mainwindow.cpp`
  - `Lab2/mainwindow.h`
- 关键实现：
  - AboutDialog.ui：label（标题）、label_2/3/4（开发者、学号、邮箱）、label_6（版本号）、buttonBox
  - AboutDialog.h / AboutDialog.cpp：构造函数只调用 ui->setupUi(this)
  - mainwindow.ui 的 actionAbout 对应帮助(&H) 菜单与工具栏末尾的“关于”按钮
  - MainWindow 增加槽 on_actionAbout_triggered，用栈上对象 dlg.exec() 打开
- 验证：
  - Debug 构建通过
  - 点“关于”弹出模态对话框，主窗口在对话框关闭前不可操作
  - 关闭对话框后主窗口编辑区仍可正常输入
- 备注：对话框用栈上对象而不是 new，避免忘记 delete 造成泄漏。

## 步骤 3 / 12：设计查找对话框

- 目标：用 Designer 设计查找对话框，并解决“对话框怎么拿到要搜索的编辑区”这个问题。
- 改动文件：
  - `Lab2/Lab2.pro`
  - `Lab2/SearchDialog.h`
  - `Lab2/SearchDialog.ui`
  - `Lab2/mainwindow.cpp`
  - `Lab2/mainwindow.h`
- 关键实现：
  - SearchDialog.ui：搜索框 + 方向单选 + 区分大小写复选框 + 查找下一个/取消按钮
  - SearchDialog.h：新增成员 QPlainTextEdit *pTextEdit，构造函数第二个参数默认 nullptr
  - MainWindow 增加槽 on_actionFind_triggered，把 ui->textEdit 传进去
  - 此步 on_btFindNext_clicked 为空实现，on_btCancel_clicked 直接 accept()
- 验证：
  - Debug 构建通过
  - 点“查找”（Ctrl+F）弹出查找对话框，默认选中“向下”
  - 点“取消”关闭对话框，主窗口不受影响
- 备注：通过构造函数注入编辑区指针，比用全局变量或 findChild 更安全，也方便第 11 步的替换窗口复用同一思路。

## 步骤 4 / 12：设计替换对话框

- 目标：在查找对话框的基础上加“替换为”输入框和两个替换按钮，形成替换窗口的骨架。
- 改动文件：
  - `Lab2/Lab2.pro`
  - `Lab2/mainwindow.cpp`
  - `Lab2/mainwindow.h`
  - `Lab2/replacedialog.h`
  - `Lab2/replacedialog.ui`
- 关键实现：
  - ReplaceDialog.ui：searchText、targetText、rbUp/rbDown、cbCaseSensitive、btFindNext、btReplace、btAllReplace、btCancel
  - ReplaceDialog.h / .cpp：与 SearchDialog 同构，新增 pTextEdit 成员
  - mainwindow.ui 中 actionReplace 已存在于格式(&O) 菜单和工具栏，此步接上槽函数
- 验证：
  - Debug 构建通过
  - 点“替换”弹出替换对话框，两个输入框与三个按钮布局正常
  - 点“取消”正常关闭
- 备注：替换窗口复制了查找窗口的布局再做扩展，代价是两个 .ui 有重复结构，但换来互不影响。另：replacedialog.h 里最初有两个拼错的槽声明（on_btRepalce_clicked / on_btAllRepalce_clicked），既没有对应实现、也不是按钮名，链接时 moc 报 undefined reference，已删除。

## 步骤 5 / 12：处理新建文件、另存文件、保存文件、打开文件操作

- 目标：实现文件的读写闭环，并在“有未保存修改”时拦截新建、打开、退出、关闭这几个危险操作。
- 改动文件：
  - `Lab2/mainwindow.cpp`
  - `Lab2/mainwindow.h`
- 关键实现：
  - MainWindow 新增 filePath / textChanged 成员，构造函数里 textChanged = false 后调用一次 on_actionNew_triggered()
  - 四个文件动作都走 QFileDialog + QFile + QTextStream
  - userEditConfirmed() 用 QMessageBox 三按钮（Yes/No/Cancel），Yes 时复用 on_actionSave_triggered()
  - 窗口标题随脏标记加 "*"，保存或打开后清掉脏标记
- 验证：
  - Debug 构建通过
  - 新建 → 输入文字 → 标题出现 "*" → 关闭窗口弹保存提示
  - 打开一个 txt 文件，内容载入、标题变为绝对路径；修改后再打开另一个文件会先提示保存
  - 另存为可选择新路径，保存后标题更新为新路径
- 备注：userEditConfirmed() 返回 false 时所有调用点立即 return，保证“取消”真的能中止后续动作。
