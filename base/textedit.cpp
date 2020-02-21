#include "textedit.h"

#include <QTextBlock>

using ltp::base::TextEdit;

TextEdit::TextEdit(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	focusLine(1);
	// 光标位置行高亮显示
	connect(ui.insideTextEdit_, SIGNAL(cursorPositionChanged()), this, SLOT(onCurrentLineHighLight()));
	connect(ui.insideTextEdit_, SIGNAL(cursorPositionChanged()), this, SLOT(cursorChanged()));
}

TextEdit::~TextEdit()
{
}

void TextEdit::cursorChanged()
{
	// 当前行/总函数 label修改
	ui.cursorPosition_->setText(QString("%1/%2(%3%)").arg(QString("1")).arg(QString("1")).arg(QString("1")));
}

void TextEdit::onCurrentLineHighLight()
{
	QList<QTextEdit::ExtraSelection> extraSelection;
	QTextEdit::ExtraSelection selection;

	// 选中行颜色属性设置
	QColor lineColor = QColor(205, 225, 245);
	selection.format.setBackground(lineColor);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = ui.insideTextEdit_->textCursor();		// 当前光标
	selection.cursor.clearSelection();

	// 设置的selection作为当前行选中
	extraSelection.append(selection);
	ui.insideTextEdit_->setExtraSelections(extraSelection);
}

void TextEdit::focusLine(int lineNum)
{
	QTextBlock block = ui.insideTextEdit_->document()->findBlockByNumber(lineNum);
	QList<QTextEdit::ExtraSelection> extraSelection;
	QTextEdit::ExtraSelection selection;

	// 选中行颜色属性设置
	QColor lineColor = QColor(205, 225, 245);
	selection.format.setBackground(lineColor);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = QTextCursor(block);
	selection.cursor.clearSelection();

	// 设置的selection作为当前行选中
	extraSelection.append(selection);
	ui.insideTextEdit_->setExtraSelections(extraSelection);
}

void TextEdit::save()
{

}

void TextEdit::saveAs(const QString& fileName)
{

}

void TextEdit::removeLine()
{
	QTextCursor lineCursor = ui.insideTextEdit_->textCursor();		// 光标所在位置
	lineCursor.select(QTextCursor::LineUnderCursor);				// 设置为整行选中
	ui.insideTextEdit_->setTextCursor(lineCursor);
	ui.insideTextEdit_->textCursor().removeSelectedText();			// 选中进行删除操作
}

void TextEdit::copyText()
{
	ui.insideTextEdit_->copy();		// 复制功能
}

void TextEdit::pasteText()
{
	ui.insideTextEdit_->paste();	// 粘贴功能
}

void TextEdit::cutText()
{
	ui.insideTextEdit_->cut();		// 剪切功能
}

void TextEdit::recoverText()
{
	ui.insideTextEdit_->redo();		// 撤销上一编辑
}

void TextEdit::repealText()
{
	ui.insideTextEdit_->undo();		// 恢复撤销
}