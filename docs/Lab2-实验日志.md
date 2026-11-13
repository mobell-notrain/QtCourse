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
