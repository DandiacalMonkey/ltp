#include "progressdialog.h"
#include <QMouseEvent>
#include <QDebug>

using ltp::base::ProgressDialog;

ProgressDialog::ProgressDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	// 取消按钮，close按钮
	connect(ui.cancelButton_, SIGNAL(clicked()), this, SLOT(closeWindow()));
	connect(ui.titleWidget_, SIGNAL(signalClose()), this, SLOT(closeWindow()));
	// 拖动标题栏进行移动
	connect(ui.titleWidget_, SIGNAL(mouseMove(QPoint)), this, SLOT(moveDialog(QPoint)));
}

ProgressDialog::~ProgressDialog()
{

}

void ProgressDialog::moveDialog(QPoint point)
{
	// 以当前位置做偏移移动窗口
	move(x() + point.x(), y() + point.y());
}

void ProgressDialog::closeWindow()
{
	// 关闭窗口
	this->reject();
	emit siganlCancel();
}

void ProgressDialog::setContentName(const QString &text)
{
	// 设置进度条名
	ui.contentLabel_->setText(text);
}

void ProgressDialog::setTitleName(const QString &text)
{
	// 设置窗口标题名
	ui.titleWidget_->setTitleName(text);
}

void ProgressDialog::setProgressLoad(int currentNum, int totalNum)
{
	// 设置进度条加载进度
	ui.progressBar_->setMaximum(totalNum);
	ui.progressBar_->setValue(currentNum);
}